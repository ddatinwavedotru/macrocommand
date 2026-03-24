#include "gtest/gtest.h"
#include "starship.h"

void executeMove(std::shared_ptr<IMovingObject> const & obj) {
    Move(*obj).execute();
}

void executeRotate(std::shared_ptr<IRotatingObject> const & obj) {
    Rotate(*obj).execute();
}

std::shared_ptr<IMovingObject> for_moving_object_in_12_5() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IMovingObject> obj=std::make_shared<MovingObjectAdapter>(gi);
    obj->set_location(Point(12,5));
    gi->set(MovingObjectAdapter::velocity_key,Vector(-7,3));
    return obj;
}

// Для объекта, находящегося в точке (12, 5) и движущегося со скоростью (-7, 3) движение меняет положение объекта на (5, 8)
TEST(starship, for_object_in_12_5_moving_with_m7_3_moves_to_5_8) {
    auto obj=for_moving_object_in_12_5();
    executeMove(obj);
    EXPECT_EQ(obj->location(), Point(5,8));
}


std::shared_ptr<IMovingObject> for_unreadable_location_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IMovingObject> obj=std::make_shared<UnreadableLocationAdapter>(gi);
    gi->set(MovingObjectAdapter::velocity_key,Vector(-7,3));
    return obj;
}

// Попытка сдвинуть объект, у которого невозможно прочитать положение в пространстве, приводит к ошибке
TEST(starship, for_unreadable_location_object_move_is_error) {
    auto obj=for_unreadable_location_object();
    EXPECT_THROW(executeMove(obj),std::bad_optional_access);
}


std::shared_ptr<IMovingObject> for_unreadable_velocity_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IMovingObject> obj=std::make_shared<UnreadableVelocityAdapter>(gi);
    obj->set_location(Point(12,5));
    return obj;
}

//     Попытка сдвинуть объект, у которого невозможно прочитать значение мгновенной скорости, приводит к ошибке
TEST(starship, for_unreadable_velocity_object_move_is_error) {
    auto obj=for_unreadable_velocity_object();
    EXPECT_THROW(executeMove(obj),std::bad_optional_access);
}


std::shared_ptr<IMovingObject> for_fixed_position_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IMovingObject> obj=std::make_shared<FixedPositionObjectAdapter>(gi);
    return obj;
}

//     Попытка сдвинуть объект, у которого невозможно изменить положение в пространстве, приводит к ошибке
TEST(starship, for_fixed_position_object_move_is_error) {
    auto obj=for_fixed_position_object();
    EXPECT_THROW(executeMove(obj),std::runtime_error);
}

std::shared_ptr<IRotatingObject> for_rotating_object_in_12() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> obj=std::make_shared<RotatingObjectAdapter>(gi);
    obj->set_angle(Angle(12));
    gi->set(RotatingObjectAdapter::angularVelocity_key,Angle(-7));
    return obj;
}

TEST(starship, for_rotating_object_in_12_rotating_with_m7_rotates_to_5) {
    auto obj=for_rotating_object_in_12();
    executeRotate(obj);
    EXPECT_EQ(obj->angle(), Angle(5));
}


std::shared_ptr<IRotatingObject> for_unreadable_angle_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> obj=std::make_shared<UnreadableAngleAdapter>(gi);
    gi->set(RotatingObjectAdapter::angularVelocity_key,Angle(-7));
    return obj;
}

TEST(starship, for_unreadable_angle_object_rotate_is_error) {
    auto obj=for_unreadable_angle_object();
    EXPECT_THROW(executeRotate(obj),std::bad_optional_access);
}


std::shared_ptr<IRotatingObject> for_unreadable_angular_velocity_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> obj=std::make_shared<UnreadableAngularVelocityAdapter>(gi);
    obj->set_angle(Angle(12));
    return obj;
}

TEST(starship, for_unreadable_angular_velocity_object_rotate_is_error) {
    auto obj=for_unreadable_velocity_object();
    EXPECT_THROW(executeMove(obj),std::bad_optional_access);
}


std::shared_ptr<IRotatingObject> for_fixed_angle_object() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> obj=std::make_shared<FixedAngleObjectAdapter>(gi);
    return obj;
}

TEST(starship, for_fixed_angle_object_rotate_is_error) {
    auto obj=for_fixed_position_object();
    EXPECT_THROW(executeMove(obj),std::runtime_error);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
