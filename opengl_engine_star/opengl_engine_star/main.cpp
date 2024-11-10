#include "Window.h"
#include "Camera.h"
#include "Mesh.h"
#include "Renderer.h"

int main()
{    
    Window w;
    Renderer r(w.WINDOW_WIDTH, w.WINDOW_HEIGHT);
    Camera cam;
    Mesh m;

    m = read_obj("plant/indoor plant_02.obj");
    //m = read_obj("buoy.obj");

    m.initBuffers();

    w.run(r, cam, m);

    return 0;
}