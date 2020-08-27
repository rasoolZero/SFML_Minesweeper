#ifndef SelectBox_h
#define SelectBox_h
#include <SFML/Graphics.hpp>
using namespace sf;
class SelectBox : public Drawable , public Transformable
{
public:
	SelectBox(IntRect box, Color color, bool mid = 0);
	SelectBox(Color color);
	void setAlpha(char alpha);
	char getAlpha() { return this->vertices[2].color.a; }
	void fade(char alpha);
	void select(short int x);
	void select();
	void deselect();
	void setCenter(short int x);
	void moveCenter(short int amount);
	void setBox(IntRect box, bool mid = 0);
	virtual void draw(RenderTarget& target, RenderStates states = RenderStates::Default) const; // from Drawable
private:
	short int width;
	short int xChange; 
	short int xDest; // target for x of center
	char aChange;
	VertexArray vertices;
};

#endif // !SelectBox_h


