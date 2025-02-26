#include <zg/entities/Plane.hpp>
#include <zg/utilities.hpp>
using namespace zg::entities;
Plane::Plane(zg::Window &window, zg::Scene &scene, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
			 glm::vec2 size, glm::vec4 color, const zg::shaders::RuntimeConstants &constants, std::string_view name) : zg::Entity(window,
																																  zg::mergeVectors<std::string_view>(
																																	  {{"Color", "Position", "Normal", "View", "Projection", "Model", "CameraPosition"}}, constants),
																																  6, {0, 1, 2, 2, 3, 0}, 4,
																																  {
																																	  {-size.x / 2, -size.y / 2, 0},
																																	  {size.x / 2, -size.y / 2, 0},
																																	  {size.x / 2, size.y / 2, 0},
																																	  {-size.x / 2, size.y / 2, 0} // Front
																																  },
																																  position, rotation, scale, name.empty() ? "Plane " + std::to_string(++planesCount) : name),
																													   uvs({{}, {}, {}, {}}), scene(scene), size(size)
{
	computeNormals(indices, positions, normals);
	updateIndices(indices);
	setColor(color);
	updateElements("Position", positions);
	updateElements("Normal", normals);
};
Plane::Plane(zg::Window &window, zg::Scene &scene, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale,
			 glm::vec2 size, textures::Texture &texture, const zg::shaders::RuntimeConstants &constants,
			 std::string_view name) : zg::Entity(window,
												 zg::mergeVectors<std::string_view>(
													 {{"UV2", "Position", "Normal", "Texture2D", "View", "Projection", "Model", "CameraPosition"}}, constants),
												 6,
												 {
													 0, 1, 2, 2, 3, 0 // Front face
												 },
												 4,
												 {
													 {-size.x / 2, -size.y / 2, 0},
													 {size.x / 2, -size.y / 2, 0},
													 {size.x / 2, size.y / 2, 0},
													 {-size.x / 2, size.y / 2, 0} // Front
												 },
												 position, rotation, scale, name.empty() ? "Plane " + std::to_string(++planesCount) : name),
									  colors({{}, {}, {}, {}}), uvs({
																	// Front face
																	{0, 0}, // 0
																	{1, 0}, // 1
																	{1, 1}, // 2
																	{0, 1}	// 3
																}),
									  scene(scene), texturePointer(&texture), size(size)
{
	switch (window.iRenderer->renderer)
	{
	default:
		break;
	case RENDERER_VULKAN:
	case RENDERER_METAL:
		flipUVsY(uvs);
		break;
	}
	computeNormals(indices, positions, normals);
	updateIndices(indices);
	updateElements("UV2", uvs);
	updateElements("Position", positions);
	updateElements("Normal", normals);
};
bool Plane::preRender()
{
	const auto &model = getModelMatrix();
	shader->bind(*this);
	scene.entityPreRender(*this);
	shader->setBlock("Model", *this, model);
	shader->setBlock("View", *this, scene.view.matrix);
	shader->setBlock("Projection", *this, scene.projection.matrix);
	shader->setBlock("CameraPosition", *this, scene.view.position, 16);
	if (texturePointer)
		shader->setTexture("Texture2D", *this, *texturePointer, 0);
	shader->unbind();
	return true;
};
void Plane::setColor(glm::vec4 color)
{
	colors = {color, color, color, color};
	updateElements("Color", colors);
};
void Plane::setSize(glm::vec2 size)
{
	positions = {
		{-size.x / 2, -size.y / 2, 0},
		{size.x / 2, -size.y / 2, 0},
		{size.x / 2, size.y / 2, 0},
		{-size.x / 2, size.y / 2, 0} // Front
	};
	updateElements("Position", positions);
	this->size = size;
};
