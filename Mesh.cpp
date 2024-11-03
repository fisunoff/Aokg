#include "Mesh.h"

Mesh::Mesh() {
	indexCount = 0;
	bufferIds[0] = 0;
	bufferIds[1] = 0;
	glGenBuffers(2, bufferIds);
}
void Mesh::load(string filename) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	// отображение вершины (по используемым ею атрибутам) на индекс в массиве вершин
	map<string, int> vertexToIndexTable;
	ifstream file(filename);
	// вектор для хранения геометрических координат
	vector<vec3> v;
	// вектор для хранения нормалей
	vector<vec3> n;
	// вектор для хранения текстурных координат
	vector<vec3> t;
	// вектор для хранения индексов атрибутов, для построения вершин
	vector<ivec3> fPoints;
	int index = 0;
	while (!file.eof()) {
		string param;
		file >> param;
		if (param == "v") {
			float x, y, z;
			file >> x >> y >> z;
			v.push_back(vec3(x, y, z));
		}
		else if (param == "vt") {
			float x, y, z;
			file >> x >> y >> z;
			t.push_back(vec3(x, y, z));
		}
		else if (param == "vn") {
			float x, y, z;
			file >> x >> y >> z;
			n.push_back(vec3(x, y, z));
		}
		else if (param == "f") {
			string str;
			for (int i = 0; i < 3; i++)
			{
				ivec3 face;
				file >> str;
				map<string, int>::iterator iter = vertexToIndexTable.find(str);
				if (iter != vertexToIndexTable.end())
				{
					indices.push_back(iter->second);
					continue;
				}
				stringstream ss(str);
				string temp;
				getline(ss, temp, '/');
				face[0] = stoi(temp);
				getline(ss, temp, '/');
				face[1] = stoi(temp);
				getline(ss, temp, '/');
				face[2] = stoi(temp);
				vertexToIndexTable.insert(make_pair(str, index));
				indices.push_back(index++);
				fPoints.push_back(face);
			}
		}

	}
	for (glm::ivec3& index : fPoints)
	{
		Vertex vert;
		vert.coord = v[index.x - 1];
		vert.texCoord = t[index.y - 1];
		vert.normal = n[index.z - 1];

		vertices.push_back(vert);
	}
	indexCount = indices.size();
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	file.close();
}

void Mesh::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferIds[1]);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, coord));
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};