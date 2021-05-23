#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;
void DrawRectangle(float  x, float y, int WIDTH, int HEIGHT);
void HandleKeyboard(GLFWwindow* window);
class gameManager {
public:
	float WIDTH = 1280;
	float HEIGHT = 720;
};

class Player {
public:
	float x;
	float y;
	float width;
	float height;
	float dx = 0;
	float dy = 0;
	void init(float xx, float yy, int wWidth, int hHeight) {
		x = xx;
		y = yy;
		width = wWidth;
		height = hHeight;
	}
	void Update(double dt) {
		y += dy * dt;

		if (y < -height / 2) {
			y = 720 - height / 2;
		}
		if (y > 720 - height / 2) {
			y = -height / 2;
		}
		dy *= 0.5;
	}
	void Render() {
		DrawRectangle(x, y, width, height);
	}
};


gameManager game;
Player player1;
Player player2;

int main(void)
{
	double dt;

	GLFWwindow* window;

	player1.init(15, 360, 15, 60);
	player2.init(game.WIDTH - 30, 360, 15, 60);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow((int)game.WIDTH, (int)game.HEIGHT, "HEIGHT", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	//VSync
	glfwSwapInterval(0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);
		dt = glfwGetTime();
		glfwSetTime(0);

		/* Update*/
		HandleKeyboard(window);
		player1.Update(dt);
		player2.Update(dt);

		/* Render here */
		glColor3f(1.0F, 1.0F, 1.0F);
		player1.Render();
		player2.Render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void HandleKeyboard(GLFWwindow* window)
{
	int S = glfwGetKey(window, GLFW_KEY_S);
	if (S == GLFW_PRESS)
	{
		player1.dy = 600;
	}
	int W = glfwGetKey(window, GLFW_KEY_W);
	if (W == GLFW_PRESS)
	{
		player1.dy = -600;
	}
	int DOWN = glfwGetKey(window, GLFW_KEY_DOWN);
	if (DOWN == GLFW_PRESS)
	{
		player2.dy = 600;
	}
	int UP = glfwGetKey(window, GLFW_KEY_UP);
	if (UP == GLFW_PRESS)
	{
		player2.dy = -600;
	}

}
void DrawRectangle(float  x, float y, int WIDTH, int HEIGHT) {
	float startX;
	float startY;
	float width = game.WIDTH;
	float height = game.HEIGHT;
	startX = (x - width / 2) / (width / 2);
	startY = -(y - height / 2) / (height / 2);

	float endX = startX + WIDTH / width * 2;
	float endY = startY + -HEIGHT / height * 2;

	glRectf(startX, startY, endX, endY);

}