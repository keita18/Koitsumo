//! @file 		Block.cpp
//! @author 	Keita Tanji
//! @breif		

#include "Block.h"
#include "pch.h"
#include "BlockContainer.h"
#include "OneYenBlock.h"
#include "FiveYenBlock.h"
#include "TenYenBlock.h"
#include "FiftyYenBlock.h"
#include "HundredYenBlock.h"
#include "FiveHundredYenBlock.h"
#include "Classes/Graphics/2D/Sprite.h"
//@TODO
//#include "SoundDriver.h"
#include "Parameter.h"
#include "PuzzleUnit.h"
#include "Classes/Math/Matrix23.h"
#include "Classes/Math/Vector2.h"

namespace Puzzle { 
/*static*/ int Block::WIDTH = 0;
/*static*/ int Block::HEIGHT = 0;
/*static*/ int Block::MAX_X = 0;
/*static*/ int Block::MAX_Y = 0;

/*static*/UserInterface::UI_GameMain* Block::uiGameMain = 0;
/*static*/float Block::FALL_SPEED = BLOCK_DEFAULT_SPEED;
/*static*/float Block::FIXED_FALL_SPEED = BLOCK_FIXED_FALL_SPEED;

//=============================================================================
/*static*/ void Block::onDecideScreenRatio(int ratio)
{
	//Stage側にratioがかかっているのでここでは必要ない
	WIDTH = Stage::WIDTH/8;
	HEIGHT = Stage::HEIGHT/8;
	MAX_X = Stage::WIDTH - WIDTH;
	MAX_Y = Stage::HEIGHT - HEIGHT;

	LOGI("Block::onDecideScreenRatio, W=%d, H=%d, MX=%d, MY=%d", WIDTH, HEIGHT, MAX_X, MAX_Y);
}

//=============================================================================
/*static*/Block* Block::create( int value, int row, int col )
{
	Block* block;
	float x = col * WIDTH;
	float y = row * HEIGHT;
	Math::Vector2 pos( x, y );
	
	LOGI("Block::create, pos=(%3.3f, %3.3f), row=%d, col=%d, val=%d", pos.x, pos.y, row, col, value);

	switch( value ){
		case 1:
			block = new OneYenBlock( pos ); break;
		case 5:
			block = new FiveYenBlock( pos ); break;
		case 10:
			block = new TenYenBlock( pos ); break;
		case 50:
			block = new FiftyYenBlock( pos ); break;
		case 100:
			block = new HundredYenBlock( pos ); break;
		case 500:
			block = new FiveHundredYenBlock( pos ); break;
		default:
			assert( !"illegal value used" );
			break;
	}
	return block;
}

//=============================================================================	
Block::Block( int value, const char* resname, Math::Vector2 pos/*使えなくなった=(WIDTH * 3, 0.0f)*/ )
	: value_( value )
	, position_( pos )
	, isLocked_( false )
	, isLinked_( false )
	, isGroup_( false )
	, speed_( FALL_SPEED )
	, ui_( 0 )
{
	if (uiGameMain) 
	{
		ui_ = uiGameMain->addCoin((UserInterface::UI_GameMain::Coin::TYPE)value);
		ui_->setPosition(&position_);
	}
}
//=============================================================================
Block::~Block() 
{
//	if (ui_ && uiGameMain) 
//		uiGameMain->removeCoin(ui_);
}
//=============================================================================
void Block::calc( float dt )
{
	if( isLocked() ){
		return;
	}
	
	//NSLog( @"value = %d, col = %d, row = %d", value_, getColumnNumber(), getRowNumber() );
	
	position_.y += speed_ * dt;

	int column = getColumnNumber();
	int nbRow = BlockContainer::getSize(column);
	int maxY = Stage::HEIGHT - ((nbRow + 1) * HEIGHT);
	// ブロック固定
	if( position_.y > maxY ){
		int row = nbRow + 1;
		BlockContainer::push( column, this );
		setPosition( Math::Vector2(column * WIDTH, Stage::HEIGHT - (row * HEIGHT)) );
		setSpeed( FIXED_FALL_SPEED );
		setLocked( true );
		ExecuteDropEffect();
	}
}
//=============================================================================
void Block::draw()
{
//	int x = (int)position_.x + Stage::getOffsetX();
//	int y = (int)position_.y + Stage::getOffsetY(); 
//	[sprite_ drawWithFrame:0 x:x y:y width:-1 height:-1];
}
//=============================================================================
int Block::getRowNumber() const
{
	return (int)( Stage::HEIGHT - HEIGHT - position_.y + HEIGHT/2 ) / HEIGHT;
}
//=============================================================================
void Block::setColumnNumber( int col )
{
	position_.x = col * WIDTH;
}
//=============================================================================
int Block::getColumnNumber() const
{
	return (int)(position_.x + WIDTH/2) / WIDTH;
}
//=============================================================================
bool Block::checkGroup( int* sumValue, BlockArray* linkBlocks )
{
	if( !isLocked() || isGroup() ){
		return false;
	}
	
	int col = getColumnNumber();
	int row = getRowNumber();
	if( col < 0 || row < 0 ){
		return false;
	}
			
	Block* targetBlocks[] = {
		BlockContainer::get( row, col + 1 ), //右
		BlockContainer::get( row + 1, col ), //上
		BlockContainer::get( row - 1, col ), //下
		BlockContainer::get( row, col - 1 ), //左
	};
	
	for( int i = 0, num = sizeof( targetBlocks )/ sizeof( targetBlocks[0] ); i < num; ++i ){
		Block* tBlock = targetBlocks[i];
		if( tBlock ){
			int tValue = tBlock->getValue();
			if( value_ == tValue && !tBlock->isLinked() && !tBlock->isGroup() ){
				if( !this->isLinked() ){
					this->setLinked( true );
				}
				tBlock->setLinked( true );
				linkBlocks->push_back( tBlock );
				//合計
				*sumValue += value_;
				// 再帰的にチェック
				tBlock->checkGroup( sumValue, linkBlocks );
			}
		}
	}
	
	return (*sumValue >= getGroupValue());
}
//=============================================================================
void Block::rotateByDeviceRotation( int angle )
{
	using Math::Vector2;
	using Math::Matrix23;
	
	Vector2 blockCenter = getPosition();
	blockCenter += Vector2( WIDTH/2.0f, HEIGHT/2.0f ); 
	
	Vector2 stageCenter( Stage::WIDTH/2.0f, Stage::HEIGHT/2.0f );
	
	Matrix23 rotateMat;
	rotateMat.setTranslation( stageCenter );
	rotateMat.rotate( (float)angle );
	rotateMat.translate( -stageCenter.x, -stageCenter.y );
	rotateMat.mul( &blockCenter, blockCenter );
	
	Vector2 result = blockCenter;
	result -= Vector2( WIDTH/2.0f, HEIGHT/2.0f );
	
	setPosition(result);
}
//=============================================================================
void Block::moveUItoFront()
{
	uiGameMain->moveCoinFront(ui_);
}

}/*namespace Puzzle*/