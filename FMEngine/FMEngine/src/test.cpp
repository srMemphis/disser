#include <iostream>
#include "src/test.h"
#include "src/Core/App.h"

#include "external/glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "external/GLFW/include/GLFW/glfw3.h"


#include <stdlib.h>
#include <stdio.h>




namespace FMEngine
{


	void hello()
	{
		printf("Hello ebanat");
	}

	void GLFWhello()
	{





  
            GLFWwindow* window;


            if (!glfwInit())
                exit(EXIT_FAILURE);

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   

            window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
            if (!window)
            {
                glfwTerminate();
                exit(EXIT_FAILURE);
            }



            glfwMakeContextCurrent(window);
            gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            glfwSwapInterval(1);


            while (!glfwWindowShouldClose(window))
            {
               

                glfwSwapBuffers(window);
                glfwPollEvents();
            }

            glfwDestroyWindow(window);

            glfwTerminate();
            exit(EXIT_SUCCESS);
        
	}

}