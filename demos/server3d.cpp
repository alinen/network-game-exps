#include "atkui/framework.h"
#include "server.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {
  }

  virtual void scene() {
    
    vec3 pos = mSocket.readPos();

    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    drawSphere(pos, radius);

    drawText("SERVER", 10, 50);
  }

  ServerSocket mSocket;
};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
