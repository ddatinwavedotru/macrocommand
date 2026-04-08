#include "gtest/gtest.h"
#include "starship.h"

void executeMove(std::shared_ptr<IMovingObject> const & obj) {
    Move(obj).execute();
}

void executeRotate(std::shared_ptr<IRotatingObject> const & obj) {
    Rotate(obj).execute();
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

std::shared_ptr<IObjectThatCanHaveFuel> for_object_having_fuel() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    BurningFuelObjectAdapter bf(gi);
    bf.set_fuelAmount(1);
    return std::make_shared<ObjectThatCanHaveFuelAdaptor>(gi);
}

void executeFuelCheck(std::shared_ptr<IObjectThatCanHaveFuel> const & hf) {
    CheckFuelCommand(hf).execute();
}

// Реализовать класс CheckFuelComamnd и тесты к нему.
TEST(starship, for_object_having_fuel_no_throw) {
    auto obj=for_object_having_fuel();
    EXPECT_NO_THROW(executeFuelCheck(obj));
}

std::shared_ptr<IObjectThatCanHaveFuel> for_object_having_no_fuel() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    BurningFuelObjectAdapter bf(gi);
    bf.set_fuelAmount(0);
    return std::make_shared<ObjectThatCanHaveFuelAdaptor>(gi);
}

// Реализовать класс CheckFuelComamnd и тесты к нему.
TEST(starship, for_object_having_no_fuel_throw) {
    auto obj=for_object_having_no_fuel();
    EXPECT_THROW(executeFuelCheck(obj),std::runtime_error);
}

std::shared_ptr<ICommand> for_empty_macro_command() {
    std::shared_ptr<MacroCommand> macro=std::make_shared<MacroCommand>();
    return macro;
}

std::shared_ptr<IBurningFuelObject> for_burning_fuel_object(FuelAmount fa, FuelAmount fc) {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<BurningFuelObjectAdapter> bf=std::make_shared<BurningFuelObjectAdapter>(gi);
    bf->set_fuelAmount(fa);
    gi->set(BurningFuelObjectAdapter::fuelConsuption_key,fc);
    return bf;
}

// Реализовать класс BurnFuelCommand и тесты к нему.
TEST(starship, for_burning_fuel_object_burns) {
    auto bf=for_burning_fuel_object(10,1);
    BurnFuelCommand cmd(bf);
    EXPECT_NO_THROW(cmd.execute());
    EXPECT_EQ(bf->fuelAmount(),9);
}


void execute(std::shared_ptr<ICommand> const & cmd) {
    cmd->execute();
}

// Реализовать простейшую макрокоманду и тесты к ней. Здесь простейшая - это значит, что при выбросе исключения вся последовательность команд приостанавливает свое выполнение, а макрокоманда выбрасывает CommandException.
TEST(starship, for_empty_macro_command_no_throw) {
    auto cmd=for_empty_macro_command();
    EXPECT_NO_THROW(execute(cmd));
}

std::shared_ptr<ICommand> for_nonempty_macro_command(std::ostream & os) {
    std::shared_ptr<MacroCommand> macro=std::make_shared<MacroCommand>();
    *macro<<std::make_shared<LoggingSomethingCommand>(os);
    return macro;
}

TEST(starship,for_nonempty_macro_command_executes) {
    std::ostringstream oss;
    auto cmd=for_nonempty_macro_command(oss);
    EXPECT_NO_THROW(execute(cmd));
    EXPECT_TRUE(!oss.str().empty());
}

// Реализовать команду движения по прямой с расходом топлива, используя команды с предыдущих шагов.
std::tuple<
    std::shared_ptr<ICommand>,
    std::shared_ptr<IGameItem>,
    std::shared_ptr<IMovingObject>,
    std::shared_ptr<BurningFuelObjectAdapter>
           >
    for_move_straight_command_burning_fuel() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IMovingObject> mo=std::make_shared<MovingObjectAdapter>(gi);
    mo->set_location(Point(12,5));
    gi->set(MovingObjectAdapter::velocity_key,Vector(-7,3));

    std::shared_ptr<BurningFuelObjectAdapter> bfa=std::make_shared<BurningFuelObjectAdapter>(gi);
    bfa->set_fuelAmount(10);
    gi->set(BurningFuelObjectAdapter::fuelConsuption_key,FuelAmount(1));

    std::shared_ptr<MacroCommand> macro=std::make_shared<MacroCommand>();
    *macro<<std::make_shared<CheckFuelCommand>(
            std::make_shared<ObjectThatCanHaveFuelAdaptor>(gi)
        );
    *macro<<std::make_shared<Move>(
        mo
        );
    *macro<<std::make_shared<BurnFuelCommand>(bfa);
    return std::make_tuple(macro,gi,mo,bfa);
}

TEST(starship,for_move_straight_command_executes) {
    auto data=for_move_straight_command_burning_fuel();
    EXPECT_NO_THROW(execute(std::get<0>(data)));
    std::shared_ptr<IMovingObject> mo=std::get<2>(data);
    EXPECT_EQ(mo->location(),Point(5,8));
    std::shared_ptr<BurningFuelObjectAdapter> bfa=std::get<3>(data);
    EXPECT_EQ(bfa->fuelAmount(),9);
}

std::tuple<
    std::shared_ptr<ICommand>,
    std::shared_ptr<IVelocityAccessObject>
    >
for_change_velocity_angle_command() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> ro=std::make_shared<RotatingObjectAdapter>(gi);
    ro->set_angle(Angle(0.));

    std::shared_ptr<IVelocityAccessObject> vao=std::make_shared<VelocityAccessObjectAdapter>(gi);

    return std::make_tuple(
            std::make_shared<ChangeVelocityCommand>(ro,vao),
            vao
        );
}

// Реализовать команду для модификации вектора мгновенной скорости при повороте. Необходимо учесть, что не каждый разворачивающийся объект движется.
TEST(starship, for_change_velocity_angle_command_executes) {
    auto data=for_change_velocity_angle_command();
    // разворачивающийся объект не движется
    EXPECT_NO_THROW(execute(std::get<0>(data)));
    // разворачивающийся объект теперь будет двигаться
    auto vao=std::get<1>(data);
    vao->set_velocity(Vector(0,1));
    EXPECT_NO_THROW(execute(std::get<0>(data)));
    EXPECT_EQ(vao->velocity(),Vector(1,0));
}

std::tuple<
    std::shared_ptr<ICommand>,
    std::shared_ptr<IVelocityAccessObject>
    >
for_velocity_change_at_rotation_command() {
    std::shared_ptr<IGameItem> gi=std::make_shared<GameItem>();
    std::shared_ptr<IRotatingObject> ro=std::make_shared<RotatingObjectAdapter>(gi);
    ro->set_angle(Angle(0.));
    gi->set(RotatingObjectAdapter::angularVelocity_key,Angle(M_PI/2));

    std::shared_ptr<IVelocityAccessObject> vao=std::make_shared<VelocityAccessObjectAdapter>(gi);
    vao->set_velocity(Vector(1,0));

    // Реализовать команду поворота, которая еще и меняет вектор мгновенной скорости, если есть.
    std::shared_ptr<MacroCommand> macro=std::make_shared<MacroCommand>();
    *macro<<std::make_shared<Rotate>(ro);
    *macro<<std::make_shared<ChangeVelocityCommand>(ro,vao);
    return std::make_tuple(macro,vao);
}

// Реализовать команду для модификации вектора мгновенной скорости при повороте. Необходимо учесть, что не каждый разворачивающийся объект движется.
TEST(starship, for_velocity_change_at_rotation_command_executes) {
    auto data=for_velocity_change_at_rotation_command();
    EXPECT_NO_THROW(execute(std::get<0>(data)));
    Vector newVel=std::get<1>(data)->velocity();
    EXPECT_TRUE(std::abs(newVel.x()-0)<1e-15);
    EXPECT_TRUE(std::abs(newVel.y()-1)<1e-15);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
