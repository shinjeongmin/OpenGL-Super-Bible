#include <sb6.h>
#include <math.h>

class simpleclear_app : public sb6::application
{
public:

	void init()
	{
		static const char title[] = "OpenGL SuperBible - tessellated triangle";

		sb6::application::init();

		memcpy(info.title, title, sizeof(title));
	}

	void startup()
	{
		static const char* vs_source[] =
		{
			"#version 410 core                                                 \n"
			"                                                                  \n"
			"layout (location = 0) in vec4 offset;                             \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
			"                                                                  \n"
			"    // Add 'offset' to our hard-coded vertex position             \n"
			"    gl_Position = vertices[gl_VertexID] + offset;                 \n"
			"}                                                                 \n"
		};

		static const char* fs_source[] =
		{
			"#version 410 core                                                 \n"
			"                                                                  \n"
			"out vec4 color;                                                   \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
			"}                                                                 \n"
		};

		// tessellation control shader source
		static const char* tcs_source[] =
		{
			"#version 410 core                                                                 \n"
			"                                                                                  \n"
			"layout (vertices = 3) out;                                                        \n"
			"                                                                                  \n"
			"void main(void)                                                                   \n"
			"{                                                                                 \n"
			"    if (gl_InvocationID == 0)                                                     \n"
			"    {                                                                             \n"
			"        gl_TessLevelInner[0] = 5.0;                                               \n"
			"        gl_TessLevelOuter[0] = 5.0;                                               \n"
			"        gl_TessLevelOuter[1] = 5.0;                                               \n"
			"        gl_TessLevelOuter[2] = 5.0;                                               \n"
			"    }                                                                             \n"
			"    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
			"}                                                                                 \n"
		};

		// tessellation evaluation shader source
		static const char* tes_source[] =
		{
			"#version 410 core                                                                 \n"
			"                                                                                  \n"
			"layout (triangles, equal_spacing, cw) in;                                         \n"
			"                                                                                  \n"
			"void main(void)                                                                   \n"
			"{                                                                                 \n"
			"    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
			"                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
			"                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
			"}                                                                                 \n"
		};

		program = glCreateProgram();
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
		glCompileShader(fs);

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, vs_source, NULL);
		glCompileShader(vs);

		GLuint tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tcs, 1, tcs_source, NULL);
		glCompileShader(tcs);

		GLuint tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tes, 1, tes_source, NULL);
		glCompileShader(tes);

		glAttachShader(program, vs);
		glAttachShader(program, fs); 
		glAttachShader(program, tcs);
		glAttachShader(program, tes);

		glLinkProgram(program);

		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		// polygonmode »£√‚
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// Our rendering function
	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		// Use the program object we created earlier for rendering
		glUseProgram(program);
		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f,
			(float)cos(currentTime) * 0.6f,
			0.0f, 0.0f };

		// Update the value of input attribute 0
		glVertexAttrib4fv(0, attrib);
		// Draw Patches
		glDrawArrays(GL_PATCHES, 0, 3);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(program);
	}

private:
	GLuint program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(simpleclear_app);
