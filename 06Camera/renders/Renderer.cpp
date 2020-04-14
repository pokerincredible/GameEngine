#include "Renderer.h"
#include "../tool/Maths.h"

void Renderer::prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(Entity entity, BasicShader& shader)
{
	shader.use(); 
	glBindVertexArray(entity.getTexturedModel().getModel().getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 transformationMatrix = Math::createTransformMatrix(entity.getPosition(), entity.getRotation(), entity.getScale());
	shader.loadTransformationMatrix(transformationMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, entity.getTexturedModel().getTexture().getID());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
	shader.unUse();
}
