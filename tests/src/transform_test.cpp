#include "transform.hpp"

#include <gtest/gtest.h>

TEST(Transform, DefaultConstructor)
{
	Transform t;

	EXPECT_EQ(1, t.GetScale());
	EXPECT_EQ(0, t.GetRotation());

	EXPECT_EQ(0, t.GetTranslation().x);
	EXPECT_EQ(0, t.GetTranslation().y);
}

TEST(Transform, ConstructFromValues)
{
	Transform t(2, 45, Vector2(8,3));

	EXPECT_EQ(2, t.GetScale());
	EXPECT_EQ(45, t.GetRotation());

	EXPECT_EQ(8, t.GetTranslation().x);
	EXPECT_EQ(3, t.GetTranslation().y);
}

TEST(Transform, SetScale)
{
	Transform t;
	t.SetScale(5);

	EXPECT_EQ(5, t.GetScale());
}

TEST(Transform, Scale)
{
	Transform t;
	t.Scale(4);

	EXPECT_EQ(5, t.GetScale());
}

TEST(Transform, SetRotation)
{
	Transform t;
	t.SetRotation(-700);

	EXPECT_EQ(20, t.GetRotation());
}

TEST(Transform, Rotate)
{
	Transform t;
	t.Rotate(-500);

	EXPECT_EQ(220, t.GetRotation());
}

TEST(Transform, SetTranslation)
{
	Transform t;
	t.SetTranslation(Vector2(-7,9));

	EXPECT_EQ(-7, t.GetTranslation().x);
	EXPECT_EQ(9, t.GetTranslation().y);
}

TEST(Transform, Translate)
{
	Transform t;
	t.Translate(Vector2(6,-9));

	EXPECT_EQ(6, t.GetTranslation().x);
	EXPECT_EQ(-9, t.GetTranslation().y);
}
