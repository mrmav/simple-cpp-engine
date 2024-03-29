#pragma once

#include "Internal.h"

#include "OpenGL/Texture2D.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/Shader.h"

#include "Camera2D.h"
#include "SpritebatchItem.h"
#include "BitmapFont.h"
#include "Utils/Rectangle.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define MAX_BATCH_ITEMS 512

namespace Engine
{

	struct BatchStats
	{
		uint32_t ItemCount;
		uint32_t TotalVertices;
		uint32_t TotalTriangles;
		uint32_t Flushs;

		void Reset()
		{
			ItemCount = 0;
			TotalVertices = 0;
			TotalTriangles = 0;
			Flushs = 0;
		}

		const std::string String() const
		{
		 	using namespace std;

            string s;
            s.append("ItemCount: ");
            s.append(to_string(ItemCount));
            s.append(" TotalVertices: ");
            s.append(to_string(TotalVertices));
            s.append(" TotalTriangles: ");
            s.append(to_string(TotalTriangles));
			s.append(" Flushs: ");
            s.append(to_string(Flushs));

            return s;
		}

	};

	class Spritebatch
	{
	public:

		Spritebatch();

		~Spritebatch()
		{
			delete[] m_Vertices;
			delete[] m_Indices;

			m_VertexArray->Delete();

			_ENGINE_LOG("Spritebatch", "Deleted.")
		};

		void Begin(Shader* shader, Camera2D* camera, int16_t depth = 0, bool customView = false);
		void SetCustomView(glm::mat4 viewTransform) { m_CustomView = viewTransform; };
		void End();

		void Draw(Texture2D* texture, float x, float y, glm::vec4 tint = glm::vec4(1));
		void Draw(Texture2D* texture, float x, float y, float angle, glm::vec4 tint = glm::vec4(1), float originX = 0.5f, float originY = 0.5f);
		void Draw(Texture2D* texture, float x, float y, Rectangle<int> clipRect, glm::vec4 tint = glm::vec4(1));
		void Draw(Texture2D* texture, float x, float y, Rectangle<int> clipRect, float angle, glm::vec4 tint = glm::vec4(1), float originX = 0.5f, float originY = 0.5f);
 
		void DrawString(BitmapFont* bitmapfont, float x, float y, const char* text, glm::vec4 tint = glm::vec4(1));

		const BatchStats& GetStats() const { return m_Stats;  }

	private:

		void Flush();
		void FlushIfNeeded();
		void CreateIndices();
		void Reset();
		void DrawBatch(Texture2D* texture);

		Shader* m_Shader = nullptr;
		Camera2D* m_Camera = nullptr;
		glm::mat4 m_CustomView = glm::mat4(1);
		uint16_t m_Depth = 0;
		bool m_DrawCustomView = false;

		VertexArray* m_VertexArray = nullptr;

		std::vector<SpritebatchItem> m_BatchItems;

		VertexPositionColorTexture* m_Vertices = nullptr;
		uint16_t* m_Indices = nullptr;
		VertexPositionColorTexture* m_VerticesPtr = nullptr;
		uint16_t* m_IndicesPtr = nullptr;

		uint32_t m_BatchItemIndex = 0;

		BatchStats m_Stats;

		bool m_BeginCalled = false;



	};

}