#include <iostream>
#include <GLFW/glfw3.h>
#include <stdlib.h>
using namespace std;
void DrawRectangle(float  x, float y, int WIDTH, int HEIGHT);

void HandleKeyboard(GLFWwindow* window);

class gameManager {
public:
	float WIDTH = 1280;
	float HEIGHT = 720;
};

gameManager game;

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
			y = game.HEIGHT - height / 2;
		}
		if (y > game.HEIGHT - height / 2) {
			y = -height / 2;
		}
		dy *= 0.5;
	}
	void Render() {
		DrawRectangle(x, y, width, height);
	}
};

class Ball {
public:
	float x;
	float y;
	float width;
	float height;
	float dx;
	float dy = 0;
	void init(float xX, float yY, float wWidth, float hHeight) {
		x = xX;
		y = yY;
		width = wWidth;
		height = hHeight;
		dx = -630 + (std::rand() % (630 + 630 + 1));
		dy = -630 + (std::rand() % (630 + 630 + 1));
	}
	void Update(double dt) {
		x += dx * dt;
		y += dy * dt;
		if (y < height / 2) {
			dy = -dy;
		}
		if (y > game.HEIGHT - height / 2) {
			dy = -dy;
		}
	}
	void Render() {
		DrawRectangle(x, y, width, height);
	}
};
bool CheckCollision(Player player, Ball ball);


Player player1;
Player player2;
Ball ball;

int main(void)
{
	srand(time(NULL));

	double dt;

	GLFWwindow* window;

	player1.init(15, 360, 15, 120);
	player2.init(game.WIDTH - 30, 360, 15, 120);
	ball.init(game.WIDTH / 2, game.HEIGHT / 2, 15, 15);

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
		if (CheckCollision(player1, ball) || CheckCollision(player2, ball)) {
			ball.dx = -ball.dx;
			ball.x += ball.dx * dt;
		}

		player1.Update(dt);
		player2.Update(dt);
		ball.Update(dt);
		//cout << true << "		" << false << endl;
		/* Render here */
		glColor3f(1.0F, 1.0F, 1.0F);
		player1.Render();
		player2.Render();
		ball.Render();

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
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		ball.init(game.WIDTH / 2, game.HEIGHT / 2, 15, 15);
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

bool CheckCollision(Player player, Ball ball) {
	return (ball.x + ball.width > player.x && ball.x < player.x + player.width && ball.y + ball.height > player.y && ball.y < player.y + player.height);
}