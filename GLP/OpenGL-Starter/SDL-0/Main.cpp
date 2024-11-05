#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <string>
#include <fstream>
using namespace std;
//#define GLEW_STATIC
string LoadShader(string fileName);

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 1000;
	int height = 1000;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !


	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);

	//Put the color you want here for the background
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

	//Describe the shape by its vertices

	float vertices[] = {
		// positions             // colors
		0.0f,  0.1f / 5.0f, 0.0f,  1.0f, 1.0f, 1.0f,
		0.0f,  1.3f / 5.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.2f / 5.0f, 0.5f / 5.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		1.0f / 5.0f,  0.5f / 5.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f / 5.0f,  0.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.7f / 5.0f, -0.7f / 5.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		0.0f,  -0.3f / 5.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		-0.7f / 5.0f, -0.7f / 5.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f / 5.0f,   0.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-1.0f / 5.0f,   0.5f / 5.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		-0.2f / 5.0f,  0.5f / 5.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  1.3f / 5.0f, 0.0f,  0.0f, 1.0f, 0.0f,

		/////
		0.0f, 0.1f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.2f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.2f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};


	//Create an ID to be given at object generation
	unsigned int vbo;
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	string vs = LoadShader("simpleVertex.shader");
	const char* vertexShaderSource = vs.c_str();

	string fs = LoadShader("simpleFragment.shader");
	const char* fragmentShaderSource = fs.c_str();

	string bfs = LoadShader("blinkFragment.shader");
	const char* blinkFragmentShaderSource = bfs.c_str();

	//Create identifiers for shaders and give source
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int blinkFragmentShader;
	blinkFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(blinkFragmentShader, 1, &blinkFragmentShaderSource, NULL);
	glCompileShader(blinkFragmentShader);

	//First Shader
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//Second Shader
	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, blinkFragmentShader);
	glLinkProgram(shaderProgram2);
	glUseProgram(shaderProgram2);

	////////////////VAOs////////////////////
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	float offSetX = 0.0f;
	float offSetY = 0.0f;

	float speedX = 0.02f;
	float speedY = 0.01f;

	bool isRunning = true;
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		float speed = 0.5f;
		float timeValue = (float)SDL_GetTicks() / 1000;
		float scale = 0.1f;

		offSetX += speedX;
		offSetY += speedY;

		std::cout << vertices[6*3] + offSetX << std::endl;
		std::cout << vertices[6*9] + offSetX << std::endl;

		if ((vertices[6*3] + offSetX > 1) || (vertices[6*9] + offSetX < -1)) {
			speedX *= -1;
		}
		if ((vertices[7] + offSetY > 1) || (vertices[6 * 5 + 1] + offSetY < -1)) {
			speedY *= -1;
		}
		

		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "redShift");

		int verteLocation = glGetUniformLocation(shaderProgram, "offSet");

		int scaleLocation = glGetUniformLocation(shaderProgram, "scale");
		glUniform1f(scaleLocation, scale);


		glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);
		glUniform3f(verteLocation, offSetX, offSetY, 0.0f);

		//Draw stuff
		glDrawArrays(GL_TRIANGLE_FAN, 0, 12);

		///
		glUseProgram(shaderProgram2);
		float redColor = (sin(timeValue * speed) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue * speed + 2) / 2.0f) + 0.5f;
		float blueColor = (sin(timeValue * speed + 4) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "redShift");
		glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 13, 15);

		SDL_GL_SwapWindow(Window); // Swapbuffer
	}
	// Quit
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);


	cin.get();
	return 0;
}

string LoadShader(string fileName) {
	ifstream myFile;
	myFile.open(fileName);
	if (myFile.fail()) {
		cerr << "Error - failed to open " << fileName << endl;
	}
	string fileText = "";
	string line = "";
	while (getline(myFile, line)) {
		fileText += line + '\n';
	}

	myFile.close();
	return fileText;
}