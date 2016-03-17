#ifndef DRAWABLE_H
#define DRAWABLE_H
class Drawable {
  public:
   virtual ~Drawable(){};
   virtual void draw() = 0;
   //this was taken from moveable.h:
   virtual ~Moveable() {};
   virtual void deltaMove(double framePeriod) = 0;
};

#endif