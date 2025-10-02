const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main() {\n"
	"	FragColor = ourColor;\n"
	"}\0";
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
	// "uniform mat4 mvp;"
	"void main() {\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
	"}\0";

const char *vertexShaderSource2 = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"out vec4 vertexColor;\n"
	"uniform mat4 view;\n"
	"uniform mat4 projection;\n"
	"void main() {\n"
	"	gl_Position = projection * view * vec4(aPos, 1.0);\n"
	"	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
	"}\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(0.2f, 0.5f, 1.0f, 1.0f);\n"
	"}\0";

