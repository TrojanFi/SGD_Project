#include "BlobOne.h"
#include "TextureManager.h"

BlobOne::BlobOne(){
	m_Frame = 4;
	m_Row = 0;
}

BlobOne::BlobOne(Properties props) {

}

void BlobOne::Draw() {
	TextureManager::DrawFrame(m_TextureID,m_Transform->X,m_Transform->Y,m_Width,m_Height,m_Row,m_Frame);
}

void BlobOne::Clean() {
}

void BlobOne::Update(float dt) {
}