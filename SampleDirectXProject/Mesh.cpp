#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>
#include <exception>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

#include <iostream>

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::wstring w_inputfile = std::wstring(full_path);
	std::string inputfile = std::string(w_inputfile.begin(), w_inputfile.end());

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");


	int vector_size = 0;
	for (size_t s = shapes.size(); s-- > 0; ) {
		vector_size += shapes[s].mesh.indices.size();
	}

	//list_vertices.reserve(vector_size);
	//list_indices.reserve(vector_size);

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];
				
				tinyobj::real_t tx = 0, ty = 0;
				if (index.texcoord_index >= 0)
				{
					tx = attribs.texcoords[index.texcoord_index * 2 + 0];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}

				VertexMesh vertex(SimpleMath::Vector3(vx, vy, -vz), SimpleMath::Vector2(tx / 2, ty / 2));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	vertexBuffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	indexBuffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());

	std::cout << "mesh" << std::endl;
}

Mesh::~Mesh()
{
}

VertexBuffer* Mesh::GetVertexBuffer() const
{
	return vertexBuffer;
}

IndexBuffer* Mesh::GetIndexBuffer() const
{
	return indexBuffer;
}

const std::vector<VertexMesh>& Mesh::GetVertices() const
{
	return list_vertices;
}
