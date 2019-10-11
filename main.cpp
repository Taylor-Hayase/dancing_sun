/*
Dancing Sun
*/

#include <iostream>
#include <glad/glad.h>
#include <vector>

#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"

#include "WindowManager.h"

// value_ptr for glm
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Application : public EventCallbacks
{

public:

	WindowManager * windowManager = nullptr;

	// Our shader program
	std::shared_ptr<Program> prog;
    std::shared_ptr<Program> prog2;

	// Contains vertex information for OpenGL
	GLuint SunVAO, MiddleVAO, Tri1VAO, Tri2VAO;

	// Data necessary to give our triangle to OpenGL
	GLuint SunVBO1, SunVBO2;
    GLuint MiddleVBO1, MiddleVBO2;
    GLuint Tri1VBO1, Tri1VBO2;
    GLuint Tri2VBO1, Tri2VBO2;

	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	// callback for the mouse when clicked move the triangle when helper functions
	// written
	void mouseCallback(GLFWwindow *window, int button, int action, int mods)
	{
		double posX, posY;
		float newPt[2];
		if (action == GLFW_PRESS)
		{
			glfwGetCursorPos(window, &posX, &posY);
			std::cout << "Pos X " << posX <<  " Pos Y " << posY << std::endl;

			//change this to be the points converted to WORLD
			//THIS IS BROKEN< YOU GET TO FIX IT - yay!
			newPt[0] = 0;
			newPt[1] = 0;

			std::cout << "converted:" << newPt[0] << " " << newPt[1] << std::endl;
			glBindBuffer(GL_ARRAY_BUFFER, SunVAO);
			//update the vertex array with the updated points
			glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*6, sizeof(float)*2, newPt);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	//if the window is resized, capture the new size and reset the viewport
	void resizeCallback(GLFWwindow *window, int in_width, int in_height)
	{
		//get the window size - may be different then pixels for retina
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

    int numTri = 50;

	/*Note that any gl calls must always happen after a GL state is initialized */
	void initGeom()
	{
        //background
        glGenVertexArrays(1, &Tri1VAO);
        glBindVertexArray(Tri1VAO);

        //vertex buffer, positions
        glGenBuffers(1, &Tri1VBO1);
        glBindBuffer(GL_ARRAY_BUFFER, Tri1VBO1);
    
        GLfloat t1_data[] ={
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0
        };
        


         glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, t1_data, GL_DYNAMIC_DRAW);
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

         
         glGenBuffers(1, &Tri1VBO2);
         glBindBuffer(GL_ARRAY_BUFFER, Tri1VBO2);
         
        GLfloat t1_color[] = {
            0.0, 0.0, 0.8,
            0.0, 0.0, 0.8,
            0.0, 0.0, 0.8
        };
         
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, t1_color, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        
        //****************************
         
        glBindVertexArray(0);
        
        //***************************
        //background (part2)
        glGenVertexArrays(1, &Tri2VAO);
        glBindVertexArray(Tri2VAO);

        //vertex buffer, positions
        glGenBuffers(1, &Tri2VBO1);
        glBindBuffer(GL_ARRAY_BUFFER, Tri2VBO1);
        
        GLfloat t2_data[] ={
            -1.0, -1.0, -1.0,
            -1.0, 1.0, -1.0,
            1.0, 1.0, -1.0
        };
            
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, t2_data, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glGenBuffers(1, &Tri2VBO2);
        glBindBuffer(GL_ARRAY_BUFFER, Tri2VBO2);
             
        GLfloat t2_color[] = {
            0.0, 0.0, 0.8,
            0.0, 0.0, 0.8,
            0.0, 0.0, 0.8
        };
             
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, t2_color, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
            
        //****************************
             
        glBindVertexArray(0);
            
        //***************************
        //THE SUN
		//generate the VAO
		glGenVertexArrays(1, &SunVAO);
		glBindVertexArray(SunVAO);
        

        //vertex buffer, positions
		glGenBuffers(1, &SunVBO1);
		glBindBuffer(GL_ARRAY_BUFFER, SunVBO1);
        
        vector<GLfloat> s_data;

        GLfloat twoPi = 2.0f * 3.141592;
        
        //fill in 80 points of a circle
        //triangle should be, center, circle @ time 0, circle @ time 1
       // int i = 0; //index for array
        int a = 1; //circle index
        
        //set first point
        s_data.push_back(cos(0 * twoPi / numTri));
        s_data.push_back(sin(0 * twoPi / numTri));
        s_data.push_back(0.0);

        for (int x = 1; x < numTri; x++) {
            
            cout << a * twoPi / numTri << endl;
            //loop through one triangle
            for (int y = 0; y < 3; y++) {
            
                //center point
                if (y == 1) {
                    s_data.push_back(0.0);
                    s_data.push_back(0.0);
                    s_data.push_back(0.0);
                }
                else { //either end of one tri or begining on another
                    s_data.push_back(cos(a * twoPi / numTri));
                    s_data.push_back(sin(a * twoPi / numTri));
                    
                    if (a % 2 == 0) {
                        s_data.push_back(0.0);
                    }
                    else {
                        s_data.push_back(1.0);
                    }
                }
               
            }
            a++;

            
        }
        s_data.push_back(cos(a * twoPi / numTri));
        s_data.push_back(sin(a * twoPi / numTri));
        s_data.push_back(0.0);
        
        s_data.push_back(0.0);
        s_data.push_back(0.0);
        s_data.push_back(0.0);


		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * s_data.size(), s_data.data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        
        glGenBuffers(1, &SunVBO2);
        glBindBuffer(GL_ARRAY_BUFFER, SunVBO2);
        
        vector<GLfloat> s_color;
        
        for (int i = 0; i < numTri * 3; i++) {
            s_color.push_back(0.95);
            s_color.push_back(0.65);
            s_color.push_back(0.55);
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * s_color.size(), s_color.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
        //****************************
        
        glBindVertexArray(0);
        
        
        
        //middle of the sun
        //***************************
        glGenVertexArrays(1, &MiddleVAO);
        glBindVertexArray(MiddleVAO);
         

        //vertex buffer, positions
        glGenBuffers(1, &MiddleVBO1);
        glBindBuffer(GL_ARRAY_BUFFER, MiddleVBO1);
         
        vector<GLfloat> m_vertex;
         
        a = 1; //circle index
        float r = 0.6;
         
        //set first point
        m_vertex.push_back(r*cos(0 * twoPi / numTri));
        m_vertex.push_back(r*sin(0 * twoPi / numTri));
        m_vertex.push_back(2.0);

        for (int x = 1; x < numTri; x++) {
            //loop through one triangle
            for (int y = 0; y < 3; y++) {
                //center point
                if (y == 1) {
                    m_vertex.push_back(0.0);
                    m_vertex.push_back(0.0);
                    m_vertex.push_back(0.0);
                }
                else { //either end of one tri or begining on another
                    m_vertex.push_back(r*cos(a * twoPi / numTri));
                    m_vertex.push_back(r*sin(a * twoPi / numTri));
                    m_vertex.push_back(2.0);
                }
            }
            a++;
        }
        m_vertex.push_back(r*cos(a * twoPi / numTri));
        m_vertex.push_back(r*sin(a * twoPi / numTri));
        m_vertex.push_back(2.0);
         
        m_vertex.push_back(0.0);
        m_vertex.push_back(0.0);
        m_vertex.push_back(0.0);


        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_vertex.size(), m_vertex.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

         
        glGenBuffers(1, &MiddleVBO2);
        glBindBuffer(GL_ARRAY_BUFFER, MiddleVBO2);
         
        vector<GLfloat> m_color;
        
        for (int i = 0; i < numTri * 3; i++) {
            m_color.push_back(0.96);
            m_color.push_back(0.94);
            m_color.push_back(0.60);
        }
         
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_color.size(), m_color.data(), GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
         
		glBindVertexArray(0); //do this at very end

	}

	//General OGL initialization - set OGL state here
	void init(const std::string& resourceDirectory)
	{
		GLSL::checkVersion();

		// Enable z-buffer test.
		//glEnable(GL_DEPTH_TEST);

		// Initialize the GLSL program.
		prog = std::make_shared<Program>();
		prog->setVerbose(true);
		prog->setShaderNames(resourceDirectory + "/shader_vertex.glsl", resourceDirectory + "/shader_fragment.glsl");
		prog->init();
        
		prog->addUniform("time");
		prog->addAttribute("vertPos");
        prog->addAttribute("vertCol");
        
        
        prog2 = std::make_shared<Program>();
        prog2->setVerbose(true);
        prog2->setShaderNames(resourceDirectory + "/shader_vertex2.glsl", resourceDirectory + "/shader_fragment2.glsl");
        
        prog2->init();

        prog2->addAttribute("vertPos");
        prog2->addAttribute("vertCol");
	}


	/****DRAW
	This is the most important function in your program - this is where you
	will actually issue the commands to draw any geometry you have set up to
	draw
	********/
	void render()
	{
		// Get current frame buffer size.
		int width, height;
		glfwGetFramebufferSize(windowManager->getHandle(), &width, &height);
		glViewport(0, 0, width, height);

		// Clear framebuffer.
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// Draw the triangle using GLSL.
        prog2->bind();
        
        glBindVertexArray(Tri1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 9);
        glBindVertexArray(0);
        
        glBindVertexArray(Tri2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3 * 9);
        glBindVertexArray(0);
        
        prog2->unbind();
        
		prog->bind();
        
        glUniform1f(prog->getUniform("time"), glfwGetTime());
        
        //then sun rays
        glBindVertexArray(SunVAO);
		glDrawArrays(GL_TRIANGLES, 0,  9 * (numTri + 1));
		glBindVertexArray(0);
        
        //the center of sun
        glBindVertexArray(MiddleVAO);
        glDrawArrays(GL_TRIANGLES, 0,  9 * (numTri + 1));
        glBindVertexArray(0);
        
		prog->unbind();

	}

};
//******************************************************************************************
int main(int argc, char **argv)
{
	std::string resourceDir = "../../resources"; // Where the resources are loaded from
/*	if (argc >= 2)
	{
		resourceDir = argv[1];
	}*/

	Application *application = new Application();

	/* your main will always include a similar set up to establish your window
		and GL context, etc. */
	WindowManager * windowManager = new WindowManager();
	windowManager->init(480, 480);
	windowManager->setEventCallbacks(application);
	application->windowManager = windowManager;

	/* This is the code that will likely change program to program as you
		may need to initialize or set up different data and state */
	// Initialize scene.
	application->init(resourceDir);
	application->initGeom();

	// Loop until the user closes the window.
	while(! glfwWindowShouldClose(windowManager->getHandle()))
	{
		// Render scene.
		application->render();

		// Swap front and back buffers.
		glfwSwapBuffers(windowManager->getHandle());
		// Poll for and process events.
		glfwPollEvents();
	}

	// Quit program.
	windowManager->shutdown();
	return 0;
}
