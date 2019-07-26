#pragma once
#include "DxBase.h"


namespace DirectXCore
{
	struct GridRenderTile
	{
		int dataIndex;
		std::pair<int, Vector3>* positionIndex;
	};
	struct GridTile
	{
		Vector3 Position;
		Vector3 Size;
		std::vector<GameObject*> objects;
		std::vector<GridRenderTile*> tileObjects;
	};
	

	class Grid : public GameObject
	{
	public:
		Grid();
		Grid(SimpleMath::Vector3 _mapSize, int _rows, int columns);
		Grid(SimpleMath::Vector3 _mapSize, int _rows, int _columns, std::vector<GameObject*>* _objects, Camera* _camera);
		void PreUpdate(float _deltaTime) override;
		void Update(float _deltaTime) override;
		void LateUpdate(float _deltaTime) override;
		void Render() override;
		void OnCollisionEnter(Collider* _other, Vector3 _normal) override;
		void GameObjectScattering(std::vector<GameObject*> _objects);
		void SetRenderer(Renderer* _renderer) { mainRenderer = _renderer; }
		void AddRenderTile(std::map<int, RECT*> _listTileID, std::vector<int>* data, std::map<int, Vector3>* _positionList,Vector3 _scale);
		~Grid();
	private:
		Vector3 GridTileSize;
		std::vector<GridTile*>* Grids;
		Camera* camera;
		Renderer* mainRenderer;
		std::map<int, RECT*> listTileID;
	};


}