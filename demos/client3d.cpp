#include "atkui/framework.h"
#include "client.h"
using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
    mSpeed = 100;
    mPos = vec3(0,0.5, 0);
  }

  virtual void scene() {
    if (keyIsDown('W')) mPos[2] += mSpeed * dt();
    if (keyIsDown('S')) mPos[2] -= mSpeed * dt();
    if (keyIsDown('A')) mPos[0] += mSpeed * dt();
    if (keyIsDown('D')) mPos[0] -= mSpeed * dt();

    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(mPos, radius);

    mSocket.sendPos(0, mPos[0], mPos[1], mPos[2]);
    drawText("CLIENT", 10, 50);
  }

  float mSpeed;
  vec3 mPos;
  ClientSocket mSocket;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
