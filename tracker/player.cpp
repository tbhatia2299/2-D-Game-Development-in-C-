#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultisprite(name),
  collision(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  TwoWayMultisprite(s),
  collision(s.collision),
  initialVelocity(s.getVelocity())
  { }

void Player::stop() {
  setVelocity(Vector2f(0,0));
}

void Player::right() {
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
}
void Player::left()  {
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
}
void Player::up()    {
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
}
void Player::down()  {
  if ( getY() < 0.82 * (worldHeight-getScaledHeight())) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  if ( !collision )
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  stop();
}
