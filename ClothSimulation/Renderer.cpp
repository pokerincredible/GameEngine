#include "Renderer.h"

void Renderer::prepare() {
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(RawModel rawModel)
{
	glBindVertexArray(rawModel.getVaoID());
	glEnableVertexAttribArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
