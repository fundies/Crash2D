#include "helper_func.hpp"

TEST(Transform, DefaultConstructor)
{
	Transform t;

	ARE_EQ(1, t.GetScale());
	ARE_EQ(0, t.GetRotation());

	ARE_EQ(0, t.GetTranslation().x);
	ARE_EQ(0, t.GetTranslation().y);
}

TEST(Transform, ConstructFromValues)
{
	Transform t(2, 45, Vector2(8, 3));

	ARE_EQ(2, t.GetScale());
	ARE_EQ(45, t.GetRotation());

	ARE_EQ(8, t.GetTranslation().x);
	ARE_EQ(3, t.GetTranslation().y);
}

TEST(Transform, SetScale)
{
	Transform t;
	t.SetScale(5);

	ARE_EQ(5, t.GetScale());
}

TEST(Transform, Scale)
{
	Transform t;
	t.Scale(4);

	ARE_EQ(5, t.GetScale());
}

TEST(Transform, SetRotation)
{
	Transform t;
	t.SetRotation(-700);

	ARE_EQ(20, t.GetRotation());

	t.SetRotation(30);
	ARE_EQ(30, t.GetRotation());
}

TEST(Transform, Rotate)
{
	Transform t;
	t.Rotate(-500);

	ARE_EQ(220, t.GetRotation());
}

TEST(Transform, SetTranslation)
{
	Transform t;
	t.SetTranslation(Vector2(-7, 9));

	ARE_EQ(-7, t.GetTranslation().x);
	ARE_EQ(9, t.GetTranslation().y);
}

TEST(Transform, Translate)
{
	Transform t;
	t.Translate(Vector2(6, -9));

	ARE_EQ(6, t.GetTranslation().x);
	ARE_EQ(-9, t.GetTranslation().y);
}
