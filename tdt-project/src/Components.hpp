#pragma once

#include <OGRE/Ogre.h>
#include <string>
#include <array>
#include <deque>
#include <bitset>
#include <memory>
#include <numeric>
#include <utility>
#include <map>
#include <Enums.hpp>
#include <Typedefs.hpp>

struct Component
{
	static constexpr int count = 42;
	static constexpr tdt::uint NO_ENTITY = std::numeric_limits<tdt::uint>::max();
};

/**
 * Components
 * \note To be able to manually create components without blueprints, all components must have
 *       either default constructors or constructors with default values for all parameters, to be able
 *       to back components up, they need to provide a copy constructor.
 * \note As constructors are called in the EntitySystem::load_component function, strings will be read
 *       from Lua and immediately discarded. Hence it was decided to make the string parameters
 *       accepted as rvalues for faster construction.
 */

/**
 * Holds info related to physical interaction of an entity with the rest
 * of the game world.
 */
struct PhysicsComponent
{
	static constexpr int type = 0;

	PhysicsComponent(bool s = false, Ogre::Vector3 pos = Ogre::Vector3{0, 0, 0}, tdt::real hh = 0.f)
		: solid{s}, position{pos}, half_height{hh}
	{ /* DUMMY BODY */ }
	PhysicsComponent(const PhysicsComponent&) = default;
	PhysicsComponent(PhysicsComponent&&) = default;
	PhysicsComponent& operator=(const PhysicsComponent&) = default;
	PhysicsComponent& operator=(PhysicsComponent&&) = default;
	~PhysicsComponent() = default;

	bool solid;
	Ogre::Vector3 position;
	tdt::real half_height;
};

/**
 * Holds info about an entity's health and regeneration.
 */
struct HealthComponent
{
	static constexpr int type = 1;

	HealthComponent(tdt::uint max = 0, tdt::uint reg = 0,
					tdt::uint def = 0, bool a = true)
		: curr_hp{max}, max_hp{max}, regen{reg}, defense{def}, alive{a}
	{ /* DUMMY BODY */ }
	HealthComponent(const HealthComponent&) = default;
	HealthComponent(HealthComponent&&) = default;
	HealthComponent& operator=(const HealthComponent&) = default;
	HealthComponent& operator=(HealthComponent&&) = default;
	~HealthComponent() = default;

	tdt::uint curr_hp;
	tdt::uint max_hp;
	tdt::uint regen;
	tdt::uint defense;
	bool alive;
};

/**
 * Holds info about the base Lua table to be called for initializing, updating and finnishing
 * an entity as well as couple categorizing enums.
 */
struct AIComponent
{
	static constexpr int type = 2;

	AIComponent(std::string&& s = "ERROR",
				ENTITY_STATE::VAL st = ENTITY_STATE::NORMAL)
		: blueprint{std::move(s)}, state{st}
	{ /* DUMMY BODY */ }
	AIComponent(const AIComponent&) = default;
	AIComponent(AIComponent&&) = default;
	AIComponent& operator=(const AIComponent&) = default;
	AIComponent& operator=(AIComponent&&) = default;
	~AIComponent() = default;

	std::string blueprint;
	ENTITY_STATE::VAL state;
};

/**
 * Holds info related to the Ogre3D rendering library.
 */
struct GraphicsComponent
{
	static constexpr int type = 3;

	GraphicsComponent(std::string&& me = "ogrehead.mesh",
					  std::string&& ma = "Ogre", bool v = true,
					  bool manual = false, Ogre::Vector3 sc = Ogre::Vector3{0, 0, 0})
		: mesh{std::move(me)}, material{std::move(ma)},
		  visible{v}, node{nullptr}, entity{nullptr},
		  manual_scaling{manual}, scale{sc}
	{ /* DUMMY BODY */ }
	GraphicsComponent(const GraphicsComponent&) = default;
	GraphicsComponent(GraphicsComponent&&) = default;
	GraphicsComponent& operator=(const GraphicsComponent&) = default;
	GraphicsComponent& operator=(GraphicsComponent&&) = default;
	~GraphicsComponent() = default;

	std::string mesh;
	std::string material;
	bool visible;
	Ogre::SceneNode* node;
	Ogre::Entity* entity;
	bool manual_scaling;
	Ogre::Vector3 scale;
};

/**
 * Holds info related to movement, if an entity has this component it should also
 * have a Physics component (containing the entity's position), otherwise the
 * MovementSystem might not work correctly.
 */
struct MovementComponent
{
	static constexpr int type = 4;

	MovementComponent(tdt::real speed = 0.f)
		: speed_modifier{speed}, original_speed{speed}
	{ /* DUMMY BODY */ }
	MovementComponent(const MovementComponent&) = default;
	MovementComponent(MovementComponent&&) = default;
	MovementComponent& operator=(const MovementComponent&) = default;
	MovementComponent& operator=(MovementComponent&&) = default;
	~MovementComponent() = default;

	tdt::real speed_modifier;
	tdt::real original_speed;
};

/**
 * Holds info about an entity's attack types and damage.
 */
struct CombatComponent
{
	static constexpr int type = 5;

	CombatComponent(tdt::uint target = Component::NO_ENTITY, tdt::uint mi = 0,
					tdt::uint ma = 0, tdt::real cd = 0, tdt::real r = 0.f, int type = 0,
					bool p = false, std::string&& proj = "ERROR")
		: curr_target{target}, min_dmg{mi},	max_dmg{ma}, cooldown{cd}, cd_time{cd},
		  range{r}, atk_type((ATTACK_TYPE)type), pursue{p}, projectile_blueprint{std::move(proj)}
	{ /* DUMMY BODY */ }
	CombatComponent(const CombatComponent&) = default;
	CombatComponent(CombatComponent&&) = default;
	CombatComponent& operator=(const CombatComponent&) = default;
	CombatComponent& operator=(CombatComponent&&) = default;
	~CombatComponent() = default;

	tdt::uint curr_target;
	tdt::uint min_dmg;
	tdt::uint max_dmg;
	tdt::real cd_time;
	tdt::real cooldown;
	tdt::real range;
	ATTACK_TYPE atk_type;
	bool pursue;
	std::string projectile_blueprint;
};

/**
 * Represents events that happen in the game, like gold seams dropping gold,
 * curing an entity of poisoning or triggers from traps etc.
 */
struct EventComponent
{ 
	static constexpr int type = 6;

	EventComponent(EVENT_TYPE ev = EVENT_TYPE::NONE, tdt::uint t = Component::NO_ENTITY,
				   tdt::real r = 0.f, bool a = true)
		: event_type{ev}, target{t}, handler{Component::NO_ENTITY}, radius{r}, active{a}
	{ /* DUMMY BODY */ }
	EventComponent(const EventComponent&) = default;
	EventComponent(EventComponent&&) = default;
	EventComponent& operator=(const EventComponent&) = default;
	EventComponent& operator=(EventComponent&&) = default;
	~EventComponent() = default;

	EVENT_TYPE event_type;
	tdt::uint target;
	tdt::uint handler;
	tdt::real radius;
	bool active;
};

/**
 * Holds info related to direct player input applied to an entity.
 */
struct InputComponent
{
	static constexpr int type = 7;

	// TODO: Should it be ERROR or ERROR.input_handler?
	InputComponent(std::string&& handler = "ERROR.input_handler")
		: input_handler{std::move(handler)}
	{ /* DUMMY BODY */ }
	InputComponent(const InputComponent&) = default;
	InputComponent(InputComponent&&) = default;
	InputComponent& operator=(const InputComponent&) = default;
	InputComponent& operator=(InputComponent&&) = default;
	~InputComponent() = default;

	std::string input_handler;
};

/**
 * Represents a timer that after a certain amount of time can start
 * end an event (it's target).
 */
struct TimeComponent
{
	static constexpr int type = 8;

	TimeComponent(TIME_EVENT ev = TIME_EVENT::NONE, tdt::real limit = 0.f,
				  tdt::uint t = Component::NO_ENTITY)
		: curr_time{0.f}, time_limit{limit}, target{t}, event_type{ev}
	{ /* DUMMY BODY */ }
	TimeComponent(const TimeComponent&) = default;
	TimeComponent(TimeComponent&&) = default;
	TimeComponent& operator=(const TimeComponent&) = default;
	TimeComponent& operator=(TimeComponent&&) = default;
	~TimeComponent() = default;

	tdt::real curr_time;
	tdt::real time_limit;
	tdt::uint target;
	TIME_EVENT event_type;
};

/**
 * Allows an entity to cast spell by providing the mana resource.
 */
struct ManaComponent
{
	static constexpr int type = 9;

	ManaComponent(tdt::uint max = 0, tdt::uint regen = 0)
		: curr_mana{max}, max_mana{max}, mana_regen{regen}
	{ /* DUMMY BODY */ }
	ManaComponent(const ManaComponent&) = default;
	ManaComponent(ManaComponent&&) = default;
	ManaComponent& operator=(const ManaComponent&) = default;
	ManaComponent& operator=(ManaComponent&&) = default;
	~ManaComponent() = default;

	tdt::uint curr_mana;
	tdt::uint max_mana;
	tdt::uint mana_regen;
};

/**
 * Allows an entity to periodically cast a spell.
 */
struct SpellComponent
{
	static constexpr int type = 10;

	SpellComponent(std::string&& b = "ERROR", tdt::real cd = 0.f)
		: blueprint{std::move(b)}, cd_time{}, cooldown{cd}
	{ /* DUMMY BODY */ }
	SpellComponent(const SpellComponent&) = default;
	SpellComponent(SpellComponent&&) = default;
	SpellComponent& operator=(const SpellComponent&) = default;
	SpellComponent& operator=(SpellComponent&&) = default;
	~SpellComponent() = default;

	std::string blueprint;
	tdt::real cd_time;
	tdt::real cooldown;
};

/**
 * Allows scheduled production of new entities (spawners) of a given type
 * up to a maximum amount.
 */
struct ProductionComponent
{
	static constexpr int type = 11;

	ProductionComponent(std::string&& b = "ERROR", tdt::uint l = 1, tdt::real cd = 0.f)
		: product_blueprint{std::move(b)}, curr_produced{0},
		  max_produced{l}, cooldown{cd}, curr_cd{0}
	{ /* DUMMY BODY */ }
	ProductionComponent(const ProductionComponent&) = default;
	ProductionComponent(ProductionComponent&&) = default;
	ProductionComponent& operator=(const ProductionComponent&) = default;
	ProductionComponent& operator=(ProductionComponent&&) = default;
	~ProductionComponent() = default;

	std::string product_blueprint;
	tdt::uint curr_produced;
	tdt::uint max_produced;
	tdt::real cooldown;
	tdt::real curr_cd;
};

/**
 * Holds GridNode's neighbour nodes.
 * \note The neighbours are set to the maximum value of tdt::uint to
 *       fix a state when one or more neighbours weren't set (won't have that many
 *       nodes so the A* algorithm will ignore them).
 */
struct GridNodeComponent
{
	static constexpr int type = 12;
	static constexpr tdt::uint neighbour_count = 9;

	GridNodeComponent(std::array<tdt::uint, neighbour_count> neigh = std::array<tdt::uint, neighbour_count>{},
					  bool f = true, tdt::uint pos_x = 0, tdt::uint pos_y = 0, tdt::uint res = Component::NO_ENTITY)
		: neighbours(neigh), free{f}, x{pos_x}, y{pos_y}, resident{res}
	{
		neighbours.fill(Component::NO_ENTITY);
	}
	GridNodeComponent(const GridNodeComponent&) = default;
	GridNodeComponent(GridNodeComponent&&) = default;
	GridNodeComponent& operator=(const GridNodeComponent&) = default;
	GridNodeComponent& operator=(GridNodeComponent&&) = default;
	~GridNodeComponent() = default;

	std::array<tdt::uint, neighbour_count> neighbours;
	bool free;
	tdt::uint x, y; // Position in the grid.
	tdt::uint resident;
};

/**
 * References the producer of the entity that has this component.
 * (Producer == building/tile that spawned it.)
 */
struct ProductComponent
{
	static constexpr int type = 13;

	ProductComponent(tdt::uint prod_id = Component::NO_ENTITY)
		: producer{prod_id}
	{ /* DUMMY BODY */ }
	ProductComponent(const ProductComponent&) = default;
	ProductComponent(ProductComponent&&) = default;
	ProductComponent& operator=(const ProductComponent&) = default;
	ProductComponent& operator=(ProductComponent&&) = default;
	~ProductComponent() = default;

	tdt::uint producer;
};

/**
 * Holds data related to the entity's current path.
 */
struct PathfindingComponent
{
	static constexpr int type = 14;

	PathfindingComponent(std::string&& b = "ERROR", tdt::uint tar = 0,
						 tdt::uint last = 0)
		: target_id{tar}, last_id{last}, path_queue{}, blueprint{std::move(b)}
	{ /* DUMMY BODY */ }
	PathfindingComponent(const PathfindingComponent&) = default;
	PathfindingComponent(PathfindingComponent&&) = default;
	PathfindingComponent& operator=(const PathfindingComponent&) = default;
	PathfindingComponent& operator=(PathfindingComponent&&) = default;
	~PathfindingComponent() = default;
	
	tdt::uint target_id, last_id;
	std::deque<tdt::uint> path_queue;
	std::string blueprint; // Name of the table the get_cost(id1, id2) function is in.
};

/**
 * Defines a task by giving it a type, source (the task handler) and a target
 * (subject of the task). Handling of these tasks is done via the TaskHandlerComponent below.
 */
struct TaskComponent
{
	static constexpr int type = 15;

	TaskComponent(tdt::uint target_id = Component::NO_ENTITY,
				  tdt::uint source_id = Component::NO_ENTITY,
				  TASK_TYPE t_type = TASK_TYPE::NONE)
		: task_type{t_type}, source{source_id}, target{target_id},
		  complete{false}
	{ /* DUMMY BODY */ }
	TaskComponent(const TaskComponent&) = default;
	TaskComponent(TaskComponent&&) = default;
	TaskComponent& operator=(const TaskComponent&) = default;
	TaskComponent& operator=(TaskComponent&&) = default;
	~TaskComponent() = default;

	TASK_TYPE task_type;
	tdt::uint source, target;
	bool complete;
};

/**
 * Task queue and register of possible tasks, every entity that is
 * able to actually do something on it's own should have it.
 */
struct TaskHandlerComponent
{
	static constexpr int type = 16;

	TaskHandlerComponent(std::string&& b = "ERROR")
		: curr_task{Component::NO_ENTITY}, possible_tasks{}, task_queue{},
		  busy{false}, blueprint{std::move(b)}
	{  /* DUMMY BODY */ }
	TaskHandlerComponent(const TaskHandlerComponent&) = default;
	TaskHandlerComponent(TaskHandlerComponent&&) = default;
	TaskHandlerComponent& operator=(const TaskHandlerComponent&) = default;
	TaskHandlerComponent& operator=(TaskHandlerComponent&&) = default;
	~TaskHandlerComponent() = default;

	tdt::uint curr_task;
	std::bitset<(tdt::uint)TASK_TYPE::COUNT> possible_tasks;
	std::deque<tdt::uint> task_queue;
	bool busy;
	std::string blueprint;
};

/**
 * Defines a building (or a wall), by holding it's radius (of the area it takes
 * in the grid) and vector of nodes that it sits on.
 */
struct StructureComponent
{
	static constexpr int type = 17;

	StructureComponent(tdt::uint r = 1, bool wt = false)
		: radius{r}, walk_through{wt}, residences{}
	{ /* DUMMY BODY */ }
	StructureComponent(const StructureComponent&) = default;
	StructureComponent(StructureComponent&&) = default;
	StructureComponent& operator=(const StructureComponent&) = default;
	StructureComponent& operator=(StructureComponent&&) = default;
	~StructureComponent() = default;

	tdt::uint radius;
	bool walk_through;
	std::vector<tdt::uint> residences;
};

/**
 * Used for projectiles that are supposed to follow a target and deal
 * damage when they hit it.
 */
struct HomingComponent
{
	static constexpr int type = 18;

	HomingComponent(tdt::uint s = Component::NO_ENTITY,
					tdt::uint t = Component::NO_ENTITY,
					tdt::uint d = 0)
		: source{s}, target{t}, dmg{d}
	{ /* DUMMY BODY */ }
	HomingComponent(const HomingComponent&) = default;
	HomingComponent(HomingComponent&&) = default;
	HomingComponent& operator=(const HomingComponent&) = default;
	HomingComponent& operator=(HomingComponent&&) = default;
	~HomingComponent() = default;

	tdt::uint source;
	tdt::uint target;
	tdt::uint dmg;
};

/**
 * Allows to cherry pink when it comes to event handling and handle
 * only certain events. (Also, only entities with this component
 * will react to events.)
 */
struct EventHandlerComponent
{
	static constexpr int type = 19;

	EventHandlerComponent(std::string&& h = "ERROR")
		: handler{std::move(h)}, possible_events{}
	{ /* DUMMY BODY */ }
	EventHandlerComponent(const EventHandlerComponent&) = default;
	EventHandlerComponent(EventHandlerComponent&&) = default;
	EventHandlerComponent& operator=(const EventHandlerComponent&) = default;
	EventHandlerComponent& operator=(EventHandlerComponent&&) = default;
	~EventHandlerComponent() = default;

	std::string handler;
	std::bitset<(tdt::uint)EVENT_TYPE::COUNT> possible_events;
};

/**
 * Contains name of the table that contains the function
 * (called "dtor") which is called when an entity is destroyed.
 */
struct DestructorComponent
{
	static constexpr int type = 20;

	DestructorComponent(std::string b = "ERROR")
		: blueprint{std::move(b)}
	{ /* DUMMY BODY */ }
	DestructorComponent(const DestructorComponent&) = default;
	DestructorComponent(DestructorComponent&&) = default;
	DestructorComponent& operator=(const DestructorComponent&) = default;
	DestructorComponent& operator=(DestructorComponent&&) = default;
	~DestructorComponent() = default;

	std::string blueprint;
};

/**
 * Represents a gold amount an entity is holding, be it a gold seam,
 * worker minion or gold depository.
 */
struct GoldComponent
{
	static constexpr int type = 21;

	GoldComponent(tdt::uint max = 0, tdt::uint curr = 0)
		: max_amount{max}, curr_amount{curr}
	{ /* DUMMY BODY */ }
	GoldComponent(const GoldComponent&) = default;
	GoldComponent(GoldComponent&&) = default;
	GoldComponent& operator=(const GoldComponent&) = default;
	GoldComponent& operator=(GoldComponent&&) = default;
	~GoldComponent() = default;

	tdt::uint max_amount;
	tdt::uint curr_amount;
};

/**
 * Represents the faction an entity that has this
 * component if a member of.
 */
struct FactionComponent
{
	static constexpr int type = 22;

	FactionComponent(FACTION f = FACTION::NEUTRAL)
		: faction{f}
	{ /* DUMMY BODY */ }
	FactionComponent(const FactionComponent&) = default;
	FactionComponent(FactionComponent&&) = default;
	FactionComponent& operator=(const FactionComponent&) = default;
	FactionComponent& operator=(FactionComponent&&) = default;
	~FactionComponent() = default;

	FACTION faction;
};

/**
 * Represents either gold or mana cost of an entity.
 */
struct PriceComponent
{
	static constexpr int type = 23;
	
	PriceComponent(tdt::uint p = 0)
		: price{p}
	{ /* DUMMY BODY */ }
	PriceComponent(const PriceComponent&) = default;
	PriceComponent(PriceComponent&&) = default;
	PriceComponent& operator=(const PriceComponent&) = default;
	PriceComponent& operator=(PriceComponent&&) = default;
	~PriceComponent() = default;

	tdt::uint price;
};

/**
 * Holds information about an objects align states, i.e. scale,
 * model, etc for the different alignments of blocks (e.g. walls).
 */
struct AlignComponent
{
	static constexpr int type = 24;
	static constexpr int state_count = 6;

	struct AlignState
	{
		Ogre::Vector3 scale;
		Ogre::Vector3 position_offset;
		std::string mesh;
		std::string material;
	};

	AlignComponent()
		: states{}
	{ /* DUMMY BODY */ }
	AlignComponent(const AlignComponent&) = default;
	AlignComponent(AlignComponent&&) = default;
	AlignComponent& operator=(const AlignComponent&) = default;
	AlignComponent& operator=(AlignComponent&&) = default;
	~AlignComponent() = default;

	std::array<AlignState, state_count> states;
};

/**
 * Dummy component that signals that an entity having it can
 * be mined.
 */
struct MineComponent
{
	static constexpr int type = 25;
};

/**
 * Allows an entity to increase the player's mana capacity and
 * regeneration rate while it's alive.
 */
struct ManaCrystalComponent
{
	static constexpr int type = 26;

	ManaCrystalComponent(tdt::uint cap = 0, tdt::uint regen = 0)
		: cap_increase{cap}, regen_increase{regen}
	{ /* DUMMY BODY */ }
	ManaCrystalComponent(const ManaCrystalComponent&) = default;
	ManaCrystalComponent(ManaCrystalComponent&&) = default;
	ManaCrystalComponent& operator=(const ManaCrystalComponent&) = default;
	ManaCrystalComponent& operator=(ManaCrystalComponent&&) = default;
	~ManaCrystalComponent() = default;

	tdt::uint cap_increase;
	tdt::uint regen_increase;
};

/**
 * Contains the blueprint table which gets called when an entity
 * that has this component gets hit.
 */
struct OnHitComponent
{
	static constexpr int type = 27;

	OnHitComponent(std::string&& b = "ERROR", tdt::real cd = 0.f)
		: blueprint{std::move(b)}, curr_time{cd}, cooldown{cd}
	{ /* DUMMY BODY */ }
	OnHitComponent(const OnHitComponent&) = default;
	OnHitComponent(OnHitComponent&&) = default;
	OnHitComponent& operator=(const OnHitComponent&) = default;
	OnHitComponent& operator=(OnHitComponent&&) = default;
	~OnHitComponent() = default;

	std::string blueprint;
	tdt::real curr_time;
	tdt::real cooldown;
};

/**
 * Contains the blueprint that gets called when an entity that has this
 * component is created.
 */
struct ConstructorComponent
{
	static constexpr int type = 28;

	ConstructorComponent(std::string&& b = "ERROR")
		: blueprint{std::move(b)}
	{ /* DUMMY BODY */ }
	ConstructorComponent(const ConstructorComponent&) = default;
	ConstructorComponent(ConstructorComponent&&) = default;
	ConstructorComponent& operator=(const ConstructorComponent&) = default;
	ConstructorComponent& operator=(ConstructorComponent&&) = default;
	~ConstructorComponent() = default;

	std::string blueprint;
};

/**
 * Allows an entity to cause an effect (by calling it's blueprint) when
 * its triggered (stepped on) or can notify a linked entity which causes the effect.
 */
struct TriggerComponent
{
	static constexpr int type = 29;

	TriggerComponent(std::string&& b = "ERROR", tdt::real cd = 0.f, tdt::real rad = 0.f)
		: blueprint{std::move(b)}, linked_entity{Component::NO_ENTITY},
		  curr_time{0.f}, cooldown{cd}, radius{rad}
	{ /* DUMMY BODY */ }
	TriggerComponent(const TriggerComponent&) = default;
	TriggerComponent(TriggerComponent&&) = default;
	TriggerComponent& operator=(const TriggerComponent&) = default;
	TriggerComponent& operator=(TriggerComponent&&) = default;
	~TriggerComponent() = default;

	std::string blueprint;
	tdt::uint linked_entity;
	tdt::real curr_time;
	tdt::real cooldown;
	tdt::real radius;
};

/**
 * Represents the game's leveling system component, contains info about experience
 * and leveling progression as well as the blueprint that gets called on level up.
 */
struct UpgradeComponent
{
	static constexpr int type = 30;

	UpgradeComponent(std::string&& b = "ERROR", tdt::uint exp = 100, tdt::uint cap = 5)
		: blueprint{std::move(b)}, experience{0}, exp_needed{exp}, level{0}, level_cap{cap}
	{ /* DUMMY BODY */ }
	UpgradeComponent(const UpgradeComponent&) = default;
	UpgradeComponent(UpgradeComponent&&) = default;
	UpgradeComponent& operator=(const UpgradeComponent&) = default;
	UpgradeComponent& operator=(UpgradeComponent&&) = default;
	~UpgradeComponent() = default;

	std::string blueprint;
	tdt::uint experience;
	tdt::uint exp_needed;
	tdt::uint level;
	tdt::uint level_cap;
};

/**
 * Allows to keep track about notification cooldown, so that an entity
 * doesn't spam the player with messages on reoccuring events in a short
 * time period.
 */
struct NotificationComponent
{
	static constexpr int type = 31;

	NotificationComponent(tdt::real cd = 0.f)
		: curr_time{0.f}, cooldown{cd}
	{ /* DUMMY BODY */ }
	NotificationComponent(const NotificationComponent&) = default;
	NotificationComponent(NotificationComponent&&) = default;
	NotificationComponent& operator=(const NotificationComponent&) = default;
	NotificationComponent& operator=(NotificationComponent&&) = default;
	~NotificationComponent() = default;

	tdt::real curr_time;
	tdt::real cooldown;
};

/**
 * Component used to create the visual effect of an explosion, the
 * damage should be done in the explosion's constructor so that it's not
 * applied on each frame.
 */
struct ExplosionComponent
{
	static constexpr int type = 32;

	ExplosionComponent(tdt::real d = 0.f, tdt::real rad = 0.f)
		: delta{d}, max_radius{rad}, curr_radius{0.f}
	{ /* DUMMY BODY */ }
	ExplosionComponent(const ExplosionComponent&) = default;
	ExplosionComponent(ExplosionComponent&&) = default;
	ExplosionComponent& operator=(const ExplosionComponent&) = default;
	ExplosionComponent& operator=(ExplosionComponent&&) = default;
	~ExplosionComponent() = default;

	tdt::real delta;
	tdt::real max_radius;
	tdt::real curr_radius;
};

/**
 * Allows to create entities that are automatically killed (summons)
 * after a certain amount of time has passed (lifespan).
 */
struct LimitedLifeSpanComponent
{
	static constexpr int type = 33;

	LimitedLifeSpanComponent(tdt::real max = 0.f)
		: max_time{max}, curr_time{0.}
	{ /* DUMMY BODY */ }
	LimitedLifeSpanComponent(const LimitedLifeSpanComponent&) = default;
	LimitedLifeSpanComponent(LimitedLifeSpanComponent&&) = default;
	LimitedLifeSpanComponent& operator=(const LimitedLifeSpanComponent&) = default;
	LimitedLifeSpanComponent& operator=(LimitedLifeSpanComponent&&) = default;
	~LimitedLifeSpanComponent() = default;

	tdt::real curr_time;
	tdt::real max_time;
};

/**
 * Name of the entity shown in the entity viewer.
 */
struct NameComponent
{
	static constexpr int type = 34;

	NameComponent(std::string&& n = "ERROR")
		: name{std::move(n)}
	{ /* DUMMY BODY */ }
	NameComponent(const NameComponent&) = default;
	NameComponent(NameComponent&&) = default;
	NameComponent& operator=(const NameComponent&) = default;
	NameComponent& operator=(NameComponent&&) = default;
	~NameComponent() = default;

	std::string name;
};

/**
 * The amount of experience the entity yields when killed.
 */
struct ExperienceValueComponent
{
	static constexpr int type = 35;

	ExperienceValueComponent(tdt::uint v = 0)
		: value{v}
	{ /* DUMMY BODY */ }
	ExperienceValueComponent(const ExperienceValueComponent&) = default;
	ExperienceValueComponent(ExperienceValueComponent&&) = default;
	ExperienceValueComponent& operator=(const ExperienceValueComponent&) = default;
	ExperienceValueComponent& operator=(ExperienceValueComponent&&) = default;
	~ExperienceValueComponent() = default;

	tdt::uint value;
};

/**
 * Allows an entity to emit light to it's surrounding area.
 */
struct LightComponent
{
	static constexpr int type = 36;

	LightComponent() = default;
	LightComponent(const LightComponent&) = default;
	LightComponent(LightComponent&&) = default;
	LightComponent& operator=(const LightComponent&) = default;
	LightComponent& operator=(LightComponent&&) = default;
	~LightComponent() = default;

	Ogre::SceneNode* node;
	Ogre::Light* light;
};

/**
 * Contains a list of commands an entity can respond to.
 */
struct CommandComponent
{
	static constexpr int type = 37;

	CommandComponent() = default;
	CommandComponent(const CommandComponent&) = default;
	CommandComponent(CommandComponent&&) = default;
	CommandComponent& operator=(const CommandComponent&) = default;
	CommandComponent& operator=(CommandComponent&&) = default;
	~CommandComponent() = default;

	std::bitset<(tdt::uint)COMMAND_TYPE::COUNT> possible_commands;
};

/**
 * A simple incrementing counter.
 * \note The max value is not enforced and serves
 *       only for manual checking.
 */
struct CounterComponent
{
	static constexpr int type = 38;

	CounterComponent(tdt::uint max = 0)
		: curr_value{}, max_value{max}
	{ /* DUMMY BODY */ }
	CounterComponent(const CounterComponent&) = default;
	CounterComponent(CounterComponent&&) = default;
	CounterComponent& operator=(const CounterComponent&) = default;
	CounterComponent& operator=(CounterComponent&&) = default;
	~CounterComponent() = default;

	tdt::uint curr_value;
	tdt::uint max_value;
};

/**
 * Dummy component that signals that an entity having it is
 * a portal - which is used in pathfinding.
 */
struct PortalComponent
{
	static constexpr int type = 39;
};

/**
 * Tracks the current animation of an entity and is used
 * for its manipulation.
 */
struct AnimationComponent
{
	static constexpr int type = 40;

	AnimationComponent()
		: current_animation{nullptr}, possible_animations{}
	{ /* DUMMY BODY */ }
	AnimationComponent(const AnimationComponent&) = default;
	AnimationComponent(AnimationComponent&&) = default;
	AnimationComponent& operator=(const AnimationComponent&) = default;
	AnimationComponent& operator=(AnimationComponent&&) = default;
	~AnimationComponent() = default;

	Ogre::AnimationState* current_animation;
	std::bitset<ANIMATION_TYPE::COUNT> possible_animations;
};

/**
 * Allows an entity to be selected and determines the material of
 * the selection circle and select/deselect handler blueprint.
 */
struct SelectionComponent
{
	static constexpr int type = 41;

	SelectionComponent(std::string&& b = "ERROR", std::string&& m = "NO_MAT",
					   Ogre::Vector3 s = Ogre::Vector3{}, SELECTION_MARKER_TYPE t = SELECTION_MARKER_TYPE::CIRCLE)
		: blueprint{std::move(b)}, material{std::move(m)}, entity{nullptr}, scale{s}, marker_type{t}, rotation{}
	{ /* DUMMY BODY */ }
	SelectionComponent(const SelectionComponent&) = default;
	SelectionComponent(SelectionComponent&&) = default;
	SelectionComponent& operator=(const SelectionComponent&) = default;
	SelectionComponent& operator=(SelectionComponent&&) = default;
	~SelectionComponent() = default;

	std::string blueprint;
	std::string material;
	Ogre::Vector3 scale;
	Ogre::Entity* entity;
	SELECTION_MARKER_TYPE marker_type;
	Ogre::Degree rotation;
};