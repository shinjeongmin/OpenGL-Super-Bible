#include <sb6.h>
#include "eg2-8.cpp"

class simpleclear_app : public sb6::application
{
public:

	void init()
	{
		static const char title[] = "OpenGL SuperBible - render triangle";

		sb6::application::init();

		memcpy(info.title, title, sizeof(title));
	}

	void startup()
	{
		program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	virtual void render(double currentTime)
	{
		static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(program);

		glPointSize(40.0f);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(program);
	}

private:
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	GLuint vertex_array_object;
};

DECLARE_MAIN(simpleclear_app);