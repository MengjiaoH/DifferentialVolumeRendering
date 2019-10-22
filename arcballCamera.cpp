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
   ospcommon::math::vec3f up = upDir();
   ospcommon::math::vec3f target = lookDir();
   ospcommon::math::vec3f right = cross(up, target);
   ospcommon::math::vec3f pos = eyePos();
  //  std::cout << "right " << right.x << " " << right.y << " " << right.z << std::endl;
   ospcommon::math::vec3f cameraUp = cross(target, right);
  //  std::cout << "up " << cameraUp.x << " " << cameraUp.y << " " << cameraUp.z << std::endl;

   ospcommon::math::LinearSpace3f cameraToworld = 
    ospcommon::math::LinearSpace3f(right.x, cameraUp.x, target.x, 
                                   right.y, cameraUp.y, target.y,
                                   right.z, cameraUp.z, target.z);

  ospcommon::math::vec3f cameraSpace = cameraToworld * worldPos;
  cameraSpace = cameraSpace - pos;
  ospcommon::math::vec2f screenPos = ospcommon::math::vec2f(-cameraSpace.x / cameraSpace.z, -cameraSpace.y / cameraSpace.z);
  ospcommon::math::vec2f rasterPos = ospcommon::math::vec2f((screenPos.x + imgSize.x / 2 ) / imgSize.x, (screenPos.y + imgSize.y / 2 ) / imgSize.y);
  
  return ospcommon::math::vec2f(rasterPos.x * imgSize.x, rasterPos.y * imgSize.y);
 }
