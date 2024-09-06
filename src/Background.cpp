#include "Background.h"


Background::Background()
{
    res = new Resource(RES_PATH + "background.png");
    
    // top right position
	vertices[0] = 1.66f;
	vertices[1] = 1.43f;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = 1.66f;
	vertices[9] = -1.43f;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = -1.66f;
	vertices[17] = -1.43f;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = -1.66f;
	vertices[25] = 1.43f;
	vertices[26] = 0.f;

	// top right color
	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	// bottom right color
	vertices[11] = 0.0f;
	vertices[12] = 1.0f;
	vertices[13] = 0.0f;

	// bottom left color
	vertices[19] = 0.0f;
	vertices[20] = 0.0f;
	vertices[21] = 1.0f;

	// top left color
	vertices[27] = 1.0f;
	vertices[28] = 1.0f;
	vertices[29] = 0.0f;

	// top right texture coords
	vertices[6] = 1.f;
	vertices[7] = 1.f;

	// bottom right texture coords
	vertices[14] = 1.f;
	vertices[15] = 0.f;

	// bottom left texture coords
	vertices[22] = 0.f;
	vertices[23] = 0.f;

	// top left texture coords
	vertices[30] = 0.f;
	vertices[31] = 1.f;
}

Background::~Background()
{

}

void Background::create(unsigned int shader)
{
	createBuffer();
	CreateTexture(res);

	transformLoc = glGetUniformLocation(shader, "transform");
	transformGameObject = glm::scale(transformGameObject, glm::vec3(0.6f, 0.7f, 0.0f));
}

void Background::draw()
{
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
