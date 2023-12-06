#include <iostream>
#include "Renderer.h"
#include "MathUtils.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "Object.h"
#include "Material.h"
#include <ctime>

#include "Mesh.h"
#include "Triangle.h"
//void InitScene01(ray::Scene&)

int main(int, char**) {
    const int width = 400;
	const int height = 300;
    const int samples = 10;
    const int depth = 2;

    std::cout << "Hello World" << std::endl;
    ray::seedRandom(static_cast<unsigned int>(time(nullptr)));

    ray::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 400, 300);
    ray::Canvas canvas(400, 300, renderer);

    // Create camera and scene outside the main loop
    float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
    std::shared_ptr<ray::Camera> camera = std::make_shared<ray::Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);


    ray::Scene scene(8, glm::vec3{ 0 }, glm::vec3{ 0.5f, 0.7f, 1.0f });
    scene.SetCamera(camera);
    ///draws a bunch of spheres
    /*
    for (int x = -5; x < 5; x++)  // Adjust the x loop range
    {
        for (int z = -5; z < 5; z++)  // Adjust the z loop range
        {

            std::shared_ptr<ray::Material> material;

            // create random material   
            float r = ray::random01(); 
            if (r < 0.3f)		material = std::make_shared<ray::Lambertian>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f })); 
            else if (r < 0.6f)	material = std::make_shared<ray::Metal>(ray::color3_t{ ray::random(0.5f, 1.0f) }, ray::random(0, 0.5f)); 
            else if (r < 0.9f)	material = std::make_shared<ray::Dielectric>(ray::color3_t{ 1.0f }, ray::random(1.1f, 2)); 
            else				material = std::make_shared<ray::Emissive>(glm::rgbColor(glm::vec3{ ray::random(0, 360), 1.0f, 1.0f }), 5.0f); 
             
            // set random sphere radius
            float radius = ray::random(0.2f, 0.3f); 
            // create sphere using random radius and material
            auto sphere = std::make_unique<ray::Sphere>(glm::vec3{ x + ray::random(-0.5f, 0.5f), radius, z + ray::random(-0.5f, 0.5f) }, radius, material);  
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }*/
	///draws a triangle
    //auto triangleMaterial = std::make_shared<ray::Lambertian>(ray::color3_t{ 1,0,0 });
    //// Define three distinct vertices for the triangle
    //auto triangle = std::make_unique<ray::Triangle>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 1, 0 }, triangleMaterial);
    //scene.AddObject(std::move(triangle));
	///draws a cube
    auto mesh = std::make_unique<ray::Mesh>(std::make_shared<ray::Emissive>(ray::color3_t{ 0, 0, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));
	///draws a plane
    auto planeMaterial = std::make_shared<ray::Lambertian>(ray::color3_t{ 0.2f }); 
    auto plane = std::make_unique<ray::Plane>(glm::vec3{ 0, -0.3, 0 }, glm::vec3{ 0, 1, 0 }, planeMaterial);
    scene.AddObject(std::move(plane));
    

    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, 1);
    canvas.Update();

    bool quit = false;
    while (!quit) {
        // Process events
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
            break;
        }

        canvas.Clear({ 0, 0, 0, 1 });
        scene.Render(canvas, 100);
        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();

    return 0;
}
