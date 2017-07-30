#include "helper.hpp"

TEST(Transformation, DefaultConstructor)
{
	Transformation t;

	ARE_EQ(1, t.GetScale().x);
	ARE_EQ(1, t.GetScale().y);
	ARE_EQ(0, t.GetRotation());

	ARE_EQ(0, t.GetTranslation().x);
	ARE_EQ(0, t.GetTranslation().y);
}

TEST(Transformation, ConstructFromValues)
{
	Transformation t(Vector2(2,2), 45, Vector2(8, 3));

	ARE_EQ(2, t.GetScale().x);
	ARE_EQ(2, t.GetScale().y);
	ARE_EQ(45, t.GetRotation());

	ARE_EQ(8, t.GetTranslation().x);
	ARE_EQ(3, t.GetTranslation().y);
}

TEST(Transformation, SetScale)
{
	Transformation t;
	t.SetScale(Vector2(5, 5));

	ARE_EQ(5, t.GetScale().x);
	ARE_EQ(5, t.GetScale().y);
}

TEST(Transformation, Scale)
{
	Transformation t;
	t.Scale(Vector2(4,4));

	ARE_EQ(4, t.GetScale().x);
	ARE_EQ(4, t.GetScale().y);
}

TEST(Transformation, SetRotation)
{
	Transformation t;
	t.SetRotation(-700);

	ARE_EQ(20, t.GetRotation());

	t.SetRotation(30);
	ARE_EQ(30, t.GetRotation());
}

TEST(Transformation, Rotate)
{
	Transformation t;
	t.Rotate(-500);

	ARE_EQ(220, t.GetRotation());
}

TEST(Transformation, SetTranslation)
{
	Transformation t;
	t.SetTranslation(Vector2(-7, 9));

	ARE_EQ(-7, t.GetTranslation().x);
	ARE_EQ(9, t.GetTranslation().y);
}

TEST(Transformation, Translate)
{
	Transformation t;
	t.Translate(Vector2(6, -9));

	ARE_EQ(6, t.GetTranslation().x);
	ARE_EQ(-9, t.GetTranslation().y);
}
