// ======================================================================== //
// Copyright 2017-2019 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "arcballCamera.h"

ArcballCamera::ArcballCamera(const ospcommon::math::box3f &worldBounds,
                             const ospcommon::math::vec2i &windowSize)
    : zoomSpeed(1),
      invWindowSize(ospcommon::math::vec2f(1.0) / ospcommon::math::vec2f(windowSize)),
      centerTranslation(ospcommon::math::one),
      translation(ospcommon::math::one),
      rotation(ospcommon::math::one)
{
  ospcommon::math::vec3f diag = worldBounds.size();
  zoomSpeed             = ospcommon::math::max(length(diag) / 150.0, 0.001);
  diag = ospcommon::math::max(diag, ospcommon::math::vec3f(0.3f * length(diag)));

  centerTranslation =
      ospcommon::math::AffineSpace3f::translate(-worldBounds.center());
  translation =
      ospcommon::math::AffineSpace3f::translate(ospcommon::math::vec3f(0, 0, length(diag)));
  updateCamera();
}

void ArcballCamera::rotate(const ospcommon::math::vec2f &from,
                           const ospcommon::math::vec2f &to)
{
  rotation = screenToArcball(to) * screenToArcball(from) * rotation;
  updateCamera();
}

void ArcballCamera::zoom(float amount)
{
  amount *= zoomSpeed;
  translation =
      ospcommon::math::AffineSpace3f::translate(ospcommon::math::vec3f(0, 0, amount)) *
      translation;
  updateCamera();
}

void ArcballCamera::pan(const ospcommon::math::vec2f &delta)
{
  const ospcommon::math::vec3f t = ospcommon::math::vec3f(
      -delta.x * invWindowSize.x, delta.y * invWindowSize.y, 0);
  const ospcommon::math::vec3f worldt = translation.p.z * xfmVector(invCamera, t);
  centerTranslation =
      ospcommon::math::AffineSpace3f::translate(worldt) * centerTranslation;
  updateCamera();
}

ospcommon::math::vec3f ArcballCamera::eyePos() const
{
  return xfmPoint(invCamera, ospcommon::math::vec3f(0, 0, 1));
}

ospcommon::math::vec3f ArcballCamera::center() const
{
  return -centerTranslation.p;
}

ospcommon::math::vec3f ArcballCamera::lookDir() const
{
  return xfmVector(invCamera, ospcommon::math::vec3f(0, 0, 1));
}

ospcommon::math::vec3f ArcballCamera::upDir() const
{
  return xfmVector(invCamera, ospcommon::math::vec3f(0, 1, 0));
}

void ArcballCamera::updateCamera()
{
  const ospcommon::math::AffineSpace3f rot    = ospcommon::math::LinearSpace3f(rotation);
  const ospcommon::math::AffineSpace3f camera = translation * rot * centerTranslation;
  invCamera                             = rcp(camera);
}

void ArcballCamera::updateWindowSize(const ospcommon::math::vec2i &windowSize)
{
  invWindowSize = ospcommon::math::vec2f(1) / ospcommon::math::vec2f(windowSize);
}

ospcommon::math::quaternionf ArcballCamera::screenToArcball(
    const ospcommon::math::vec2f &p)
{
  const float dist = dot(p, p);
  // If we're on/in the sphere return the point on it
  if (dist <= 1.f) {
    return ospcommon::math::quaternionf(0, p.x, p.y, std::sqrt(1.f - dist));
  } else {
    // otherwise we project the point onto the sphere
    const ospcommon::math::vec2f unitDir = normalize(p);
    return ospcommon::math::quaternionf(0, unitDir.x, unitDir.y, 0);
  }
}


 ospcommon::math::vec2f ArcballCamera::worldToPixel(ospcommon::math::vec3f worldPos, ospcommon::math::vec2i imgSize)
 {
   ospcommon::math::vec3f N = lookDir();
   ospcommon::math::vec3f U = upDir();
   U = cross(U, N);
   ospcommon::math::vec3f V = cross(N, U);
   
   ospcommon::math::vec3f pos = eyePos();


   ospcommon::math::LinearSpace3f cameraToworld = 
    ospcommon::math::LinearSpace3f(U.x, V.x, N.x, 
                                   U.y, V.y, N.y,
                                   U.z, V.z, N.z);

  ospcommon::math::vec3f cameraSpace = cameraToworld * worldPos;

  ospcommon::math::vec3f v = cameraSpace - pos;

  ospcommon::math::vec3f r = normalize(v);
  
  const float denom = dot(-r, -N);
  if (denom == 0.0) {
    return ospcommon::math::vec2f(-1, -1);
  }
  
  const float t = 1.0 / denom;
  ospcommon::math::vec3f dir_00 = N - .5f * V - .5f * U;

  const ospcommon::math::vec3f screenDir = r * t - dir_00;
  ospcommon::math::vec2f sp = ospcommon::math::vec2f(dot(screenDir, normalize(V) * imgSize.x), dot(screenDir, normalize(U) * imgSize.y)) / imgSize;

  sp.x = (sp.x * 0.5f) + 0.5f;
  sp.y = (sp.y * 0.5f) + 0.5f;

  // if(sp.x <= 0.f || sp.y <= 0.f){
  //   std::cout << "sp x" << sp.x << " y" << sp.y << std::endl;
  // }




  sp = sp * imgSize;
  // const float depth = sign(t) * length(v);

  // std::cout << "screen pos = (" << sp.x << ", " << sp.y << std::endl;

  return sp;



  // ospcommon::math::vec2f screenPos = ospcommon::math::vec2f(-cameraSpace.x / (float)cameraSpace.z, -cameraSpace.y / (float)cameraSpace.z);
  // ospcommon::math::vec2f rasterPos = ospcommon::math::vec2f((screenPos.x + imgSize.x / 2 ) / imgSize.x, (screenPos.y + imgSize.y / 2 ) / imgSize.y);

  // std::cout << "camera space pos " << cameraSpace.x << " " << cameraSpace.y << " " << cameraSpace.z <<  std::endl;
  // std::cout << "screen space " << screenPos.x << " " << screenPos.y << std::endl;
  
  // return ospcommon::math::vec2f(rasterPos.x * imgSize.x, rasterPos.y * imgSize.y);
 }
