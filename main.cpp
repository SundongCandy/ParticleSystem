#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>

// Other includes
#include "Shader.h"

#include "psparticle2f.h"
#include "psparticleemitter2f.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Holds uniform value of texture mix
GLfloat mixValue = 0.2f;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);


	// Build and compile our shader program
	Shader ourShader("textures.vs", "textures.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	PsParticle2f a(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(0.0f, 1.0f), PsVector2f(0.0f, 0.0f),
		0.0f, 0.0f, 10.0f, 0.0f);
	PsParticle2f b(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(1.0f, -1.0f), PsVector2f(0.0f, 0.0f),
		0.0f, 0.0f, 10.0f, 0.0f);
	PsParticle2f c(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(-1.0f, 0.0f), PsVector2f(0.0f, 0.0f),
		0.0f, 0.0f, 10.0f, 0.0f);
	PsParticle2f d(1.0f, 2.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(-1.0f, 4.0f), PsVector2f(0.0f, 0.0f),
		0.0f, 0.0f, 10.0f, 0.0f);
	PsParticle2f e(1.0f, 1.0f, PsColor(0.871f, 0.490f, 0.173f), PsVector2f(-1.0f, -1.0f), PsVector2f(0.0f, 0.0f),
		0.0f, 0.0f, 10.0f, 0.0f);

	PsParticleEmitter2f emitter(
		150,
		PsVector2f(0.0f, 20.0f),
		PsVector2f(20.0f, 0.0f),
		20,
		1.0f,
		0.5f,
		1.0f,
		0.5f,
		PsColor(1.0f, 1.0f, 0.0f),
		PsVector2f(0.0f, 0.0f),
		PsVector2f(1.0f, 1.0f),
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		5.0f,
		2.0f,
		10.0f
		);

	int vertexNumber = 3;
	int triangleNumber = 1;

	int maxVertexNumber, maxTriangleNumber, currentVertexNumber, currentTriangleNumber;
	emitter.getMaxRenderParameter(&maxVertexNumber, &maxTriangleNumber);
	emitter.getCurrentRenderParameter(&currentVertexNumber, &currentTriangleNumber);

	//cout << "maxVertexNumber = " << maxVertexNumber << "; maxTriangleNumber = " << maxTriangleNumber << endl
	//	<< "currentVertexNumber = " << currentVertexNumber << "; currentTriangleNumber = " << currentTriangleNumber << endl;

	GLfloat *vertices2 = (GLfloat *)malloc(sizeof(float) * maxVertexNumber * 8);
	GLuint *indices2 = (GLuint *)malloc(sizeof(unsigned int) * maxTriangleNumber * 3);

	int vertices2Begin = 0;
	int indices2Begin = 0;

	emitter.getRenderDataasPart(&vertices2, &vertices2Begin, &indices2, &indices2Begin, true);

	//cout << "vertices2Begin = " << vertices2Begin << "; indices2Begin = " << indices2Begin << endl;

	a.computeAcceleration();
	b.computeAcceleration();
	c.computeAcceleration();
	d.computeAcceleration();
	e.computeAcceleration();
	/*GLfloat vertices[] = {
		// Positions          // Colors           // Texture Coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left 
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	};*/
	int particleNumber = 5;
	GLfloat *vertices = (GLfloat *)malloc(sizeof(float) * particleNumber * vertexNumber * 8);
	GLuint *indices = (GLuint *)malloc(sizeof(unsigned int) * particleNumber * triangleNumber * 3);

	int verticesBegin = 0;
	int indicesBegin = 0;

	a.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
	b.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
	c.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
	d.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
	//e.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * currentVertexNumber * 8, vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * currentTriangleNumber * 3, indices2, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO


	// Load and create a texture 
	GLuint texture1;
	GLuint texture2;
	// ====================
	// Texture 1
	// ====================
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	// ===================
	// Texture 2
	// ===================
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	image = SOIL_load_image("awesomeface.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate shader
		ourShader.Use();

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture2"), 1);

		// Set current value of uniform mix
		glUniform1f(glGetUniformLocation(ourShader.Program, "mixValue"), mixValue);

		a.move(0.001f);
		b.move(0.001f);
		c.move(0.001f);
		d.move(0.001f);
		e.move(0.001f);
		a.refreshVertices();
		b.refreshVertices();
		c.refreshVertices();
		d.refreshVertices();
		e.refreshVertices();
		verticesBegin = 0;
		indicesBegin = 0;
		a.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
		b.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
		c.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
		d.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);
		//e.getRenderDataasPart(&vertices, &verticesBegin, &indices, &indicesBegin, true);

		emitter.run(0.001f);
		emitter.getCurrentRenderParameter(&currentVertexNumber, &currentTriangleNumber);
		vertices2Begin = 0;
		indices2Begin = 0;

		emitter.getRenderDataasPart(&vertices2, &vertices2Begin, &indices2, &indices2Begin, true);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * currentVertexNumber * 8, vertices2, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * currentTriangleNumber * 3, indices2, GL_STATIC_DRAW);

		// Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		// Color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		// TexCoord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); // Unbind VAO
		

		// Draw container
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, currentTriangleNumber * 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	// Change value of uniform with arrow keys (sets amount of textre mix)
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}