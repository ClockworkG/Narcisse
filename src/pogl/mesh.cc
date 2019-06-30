#include <pogl/mesh.hh>

#include <tiny_obj_loader.h>

namespace pogl
{
    Mesh make_mesh(const fs::path& obj_path)
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string err;
        std::string warn;

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials,
                                    &warn, &err, obj_path.c_str());

        auto mesh = Mesh{};
        if (!ret)
            return mesh;

        for (size_t s = 0; s < shapes.size(); s++)
        {
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                std::size_t fv = shapes[s].mesh.num_face_vertices[f];

                for (size_t v = 0; v < fv; v++)
                {
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                    mesh.vertices.emplace_back(
                        attrib.vertices[3 * idx.vertex_index + 0],
                        attrib.vertices[3 * idx.vertex_index + 1],
                        attrib.vertices[3 * idx.vertex_index + 2]
                    );
                    mesh.normals.emplace_back(
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]
                    );
                    mesh.uv.emplace_back(
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1]
                    );
                }
                index_offset += fv;
            }
        }

        return mesh;
    }
} // namespace pogl
