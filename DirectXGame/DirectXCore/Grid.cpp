#include "stdafx.h"
#include "Grid.h"

using namespace DirectXCore;

Grid::Grid()
{
}

Grid::Grid(SimpleMath::Vector3 _mapSize, int _rows, int columns)
{

}

Grid::Grid(SimpleMath::Vector3 _mapSize, int _rows, int _columns, std::vector<GameObject*>* _objects, Camera* _camera)
{
	camera = _camera;
	Grids = new std::vector<GridTile*>();
	availableGrids = new std::vector<GridTile*>();
	Vector3 MapTileSize = Vector3(_mapSize.x / _columns, _mapSize.y / _rows, 0);
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			GridTile* gridtile = new GridTile();
			gridtile->Position = Vector3(MapTileSize.x*j + MapTileSize.x / 2, MapTileSize.y*i + MapTileSize.y / 2, 0);
			gridtile->Size = MapTileSize;

			for (size_t i = 0; i < _objects->size(); i++)
			{
				Vector3 _objectPosition = _objects->at(i)->GetTransform()->GetPosition();
				Vector3 _objectScale = _objects->at(i)->GetTransform()->GetScale();
				bool notContainX = (_objectPosition.x + _objectScale.x<gridtile->Position.x - gridtile->Size.x / 2 || _objectPosition.x - _objectScale.x>gridtile->Position.x + gridtile->Size.x / 2);
				bool notContainY = (_objectPosition.y + _objectScale.y<gridtile->Position.y - gridtile->Size.y / 2 || _objectPosition.y - _objectScale.y>gridtile->Position.y + gridtile->Size.y / 2);
				if (!notContainX && !notContainY) gridtile->objects.push_back(_objects->at(i));
			}
			Grids->push_back(gridtile);
		}
	}
}

void Grid::PreUpdate(float _deltaTime)
{
	Vector3 cameraPos = camera->GetPosition();
	Vector3 camereScale = Vector3(camera->GetWidth(), camera->GetHeight(), 0);
	availableGrids->clear();
	for (size_t j = 0; j < Grids->size(); j++)
	{
		bool notContainX = (cameraPos.x + camereScale.x<Grids->at(j)->Position.x - Grids->at(j)->Size.x / 2 || cameraPos.x - camereScale.x>Grids->at(j)->Position.x + Grids->at(j)->Size.x / 2);
		bool notContainY = (cameraPos.y + camereScale.y<Grids->at(j)->Position.y - Grids->at(j)->Size.y / 2 || cameraPos.y - camereScale.y>Grids->at(j)->Position.y + Grids->at(j)->Size.y / 2);
		if (!notContainX && !notContainY) availableGrids->push_back(Grids->at(j));
	}
	for (size_t i = 0; i < availableGrids->size(); i++) for (size_t j = 0; j < availableGrids->at(i)->objects.size(); j++) availableGrids->at(i)->objects.at(j)->PreUpdate(_deltaTime);
}

void Grid::Update(float _deltaTime)
{
	for (size_t i = 0; i < availableGrids->size(); i++)
	{
		for (size_t j = 0; j < availableGrids->at(i)->objects.size(); j++)
		{
			availableGrids->at(i)->objects.at(j)->Update(_deltaTime);
		}
	}
}

void Grid::LateUpdate(float _deltaTime)
{
	for (size_t i = 0; i < availableGrids->size(); i++)
	{
		for (size_t j = 0; j < availableGrids->at(i)->objects.size(); j++)
		{
			availableGrids->at(i)->objects.at(j)->LateUpdate(_deltaTime);
		}
	}
}

void Grid::Render()
{
	Vector3 worldToScreenShift = Vector3(camera->GetWidth() / 2 - camera->GetPosition().x, camera->GetHeight() / 2 - camera->GetPosition().y, 0);
	for (size_t i = 0; i < availableGrids->size(); i++)
	{
		//if (i != 0) break;
		for (size_t j = 0; j < availableGrids->at(i)->tileObjects.size(); j++)
		{
			
			Vector3 currentPosition = availableGrids->at(i)->tileObjects.at(j)->positionIndex->second + worldToScreenShift;
			if (camera->IsContain(currentPosition, availableGrids->at(i)->tileObjects.at(j)->tileScale))
			{
				mainRenderer->SetRECT(*listTileID[availableGrids->at(i)->tileObjects.at(j)->dataIndex]);
				mainRenderer->Render(currentPosition, Vector3(0, 0, 0), scale);
			}
		}
	}
}


void Grid::OnCollisionEnter(Collider * _other, Vector3 _normal)
{
}

void Grid::GameObjectScattering(std::vector<GameObject*> _objects)
{
}



void DirectXCore::Grid::AddRenderTile(std::map<int, RECT*> _listTileID, std::vector<int>* data, std::map<int, Vector3>* _positionList, Vector3 _scale)
{
	scale = _scale;
	listTileID = _listTileID;
	for (size_t j = 0; j < Grids->size(); j++)
	{
		for (size_t i = 0; i < _positionList->size(); i++)
		{
			Vector3 _objectPosition = _positionList->at(i);
			Vector3 _objectScale = Vector3(16 /** scale.x*/, 16 /** scale.y*/, 0);
			bool notContainX = (_objectPosition.x + _objectScale.x<Grids->at(j)->Position.x - Grids->at(j)->Size.x / 2 || _objectPosition.x - _objectScale.x>Grids->at(j)->Position.x + Grids->at(j)->Size.x / 2);
			bool notContainY = (_objectPosition.y + _objectScale.y<Grids->at(j)->Position.y - Grids->at(j)->Size.y / 2 || _objectPosition.y - _objectScale.y>Grids->at(j)->Position.y + Grids->at(j)->Size.y / 2);
			if (!notContainX && !notContainY)
			{
				GridRenderTile* renderTile = new GridRenderTile();
				renderTile->dataIndex = data->at(i);
				renderTile->positionIndex = new std::pair<int, Vector3>();
				renderTile->positionIndex->first = i;
				renderTile->positionIndex->second = _positionList->at(i);
				renderTile->tileScale = _objectScale;

				Grids->at(j)->tileObjects.push_back(renderTile);
			}
		}
		GridTile*a = Grids->at(j);
	}
}

Grid::~Grid()
{
}
