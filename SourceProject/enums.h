#pragma once

enum class TextureId
{
	Bbox                        = 0,
	Warning                     = 1,
	KeyCodeFont                 = 2,
	CrtEffect                   = 3,
	MapCharleston               = 4,
	MapBossCharlestonLight      = 5,
	MapBossCharlestonDark       = 6,
	MapPittsburghDark           = 7,
	MapPittsburghLight          = 8,
	MapRedAlert                 = 9,
	Captain                     = 10,
	Enemies                     = 11,
	Wizard                      = 12,
	Dynamite                    = 13,
	CaptainSpin = 14,
};

enum class SpriteId
{
	Invisible			            =  0,
							           
	EnemyGun_Stand			        =  1,
	EnemyGun_Walking		        =  2,
	EnemyGun_BeforeExplode          =  3,
	EnemyGun_Sitting                =  4,
	BulletEnemyGun			        =  5,

	EnemyRocket_Stand               =  6,
	EnemyRocket_Walking             =  7,
	EnemyRocket_BeforeExplode       =  8,
	EnemyRocket_Sitting             =  9,
	BulletEnemyRocket_Horizontal    = 10,
	BulletEnemyRocket_Cross         = 11,

	Explode                         = 12,

	ItemSmallPowerStone             = 13,
	ItemBigPowerStone               = 14,
	ItemFivePoint                   = 15,
	ItemOneUp                       = 16,
	ItemSmallEnergy                 = 17,
	ItemBigEnergy                   = 18,
	ItemKeyKrystal                  = 19,

	ExitSign                        = 20,
	CaptainHealth                   = 21,
	CapsuleIdle                     = 22,
	CapsuleOpenning                 = 23,
	CapsuleIdle_NoBg                = 24,
	CapsuleOpenning_NoBg            = 25,

	DoorDarkIdle                    = 26,
	DoorDarkOpenning                = 27,
	DoorLightIdle                   = 28,
	DoorLightOpenning               = 29,

	Shield_Side                     = 30,
	Shield_Straight                 = 31,
	Shield_Down                     = 32,
	Shield_Up                       = 33,

	BreakableLedge_Intact           = 35,
	BreakableLedge_Separated        = 36,
	MovingLedge                     = 37,
	FireTail_Ver                    = 38,
	FireTail_Hor                    = 39,

	Bunker_Idle_0                   = 40,
	Bunker_Idle_1                   = 41,
	Bunker_Idle_2                   = 42,
	Bunker_Idle_3                   = 43,
	Bunker_Idle_4                   = 44,
	Bunker_Idle_5                   = 45,
	Bunker_Idle_6                   = 46,
	Bunker_Idle_7                   = 47,
	Bunker_Spin                     = 48,
	Bullet_Bunker                   = 49,

	EnemyWizard_Walking     = 50,
	EnemyWizard_Stand       = 51,
	EnemyWizard_BeforeDefeated = 52,
	EnemyWizard_Defeated    = 53,
	EnemyWizard_Laught = 54,
	EnemyWizard_FlyUp       = 55,
	EnemyWizard_FlyDown = 56,
	EnemyWizard_ShootWhenFly = 57,
	EnemyWizard_ShootBullet = 58,
	EnemyWizard_ShootBulletFire = 59,
	EnemyWizard_Flying = 60,

	BulletFireEnemyWizard_Horizontal = 61,
	BulletFireEnemyWizard_Vertical = 62,
	BulletEnemyWizard_Horizontal = 63,
	BulletEnemyWizard_SemiCross = 64,
	BulletEnemyWizard_Cross = 65,

	EnemyFly_Fly = 66,
	EnemyFly_Shoot = 77,

	BulletEnemyFly_Up = 67,
	BulletEnemyFly_Down = 68,
	BulletEnemyFly_Hor = 69,
	BulletEnemyFly_CrossUp = 70,
	BulletEnemyFly_CrossDown = 71,

	ElectricBat_Sleep = 72,
	ElectricBat_StartFly = 73,
	ElectricBat_EndFly = 74,
	ElectricBat_FlyAttack = 75,
	ElectricBat_Fly = 76,

	Captain_Standing = 100,
	Captain_Walking = 101,
	Captain_Jump = 102,
	Captain_LookUp = 103,
	Captain_Sitting = 104,
	Captain_Punching = 105,
	Captain_Throw = 106, 
	Captain_Falling = 107,
	Captain_JumpKick = 108,
	Captain_SitPunch = 109,
	Captain_Smash = 110,
	Captain_Spin = 111,
	Captain_Climb = 112,
	Captain_Injure = 113,
	Captain_Dead = 114,
	Captain_Swimming = 115,
	Captain_FallToWater = 116,
	Captain_InWater = 117,
	Captain_CoverLow = 118,
	Captain_ElectricShock = 119,

	DynamiteNapalm_FallFromTheSky = 200,
	DynamiteNapalm_Standing = 201,
	DynamiteNapalm_Intact_Running = 202,
	DynamiteNapalm_ThrowDynamite = 203,
	DynamiteNapalm_Intact_Shooting = 204,
	DynamiteNapalm_Intact_Injure = 205,
	DynamiteNapalm_Headless_Standing = 206,
	DynamiteNapalm_Headless_Running_Shooting = 207,
	DynamiteNapalm_FireBullet = 210,
	DynamiteNapalm_Dynamite = 211,
	
	ElectricTrap_Active = 220,

	EnemyGun_Stand_BW  = 1001,
	EnemyGun_Walking_BW    = 1002,
	EnemyGun_BeforeExplode_BW          = 1003,
	EnemyGun_Sitting_BW      = 1004,

	EnemyRocket_Stand_BW = 1006,
	EnemyRocket_Walking_BW = 1007,
	EnemyRocket_BeforeExplode_BW = 1008,
	EnemyRocket_Sitting_BW = 1009
};

enum class SoundId
{
	Invalid          = -1,
	Greeting         =  0,
	Cursor           =  1,
	CaptainTheme     =  2,
	BossBattle       =  3,
	RedAlert         =  4,
	Ambush           =  5,
	Death            =  6,
	ItemKrystal      =  7,
	ItemEnergy       =  8,
	ItemNormal       =  9,
	BulletNormal     = 10,
	BulletLazer      = 11,
	Explosion        = 12,
	ShieldThrow      = 13,
	ShieldCollide    = 14,
	Punch            = 15,
	Tackle           = 16,
	HighJump         = 17,
	Grounding        = 18,
	Water            = 19,
	Spinning         = 20,
	DoorOpen         = Tackle,
};

enum class ClassId
{
	Captain              =   0,

	RigidBlock           =   1,
	Water                =   2,
	PassableLedge        =   3,
	ClimbableBar         =   4,
	DamageBlock          =   5,
	Switch               =   6,
	NextMap              =   7,
	Door                 =   8,
	Spawner              =   9,
	AmbushTrigger        =  10,
	Capsule              =  11,
	Bunker               =  12,
	BreakableLedge       =  13,
	MovingLedgeUpdater   =  14,
	ElectricTrap         =  15
};

enum class State
{
	Invisible,
	Destroyed,

	Camera_Normal,
	Camera_InAmbush,
	Camera_Recover,

	EnemyGun_Walking,
	EnemyGun_Stand,
	EnemyGun_Sitting,
	EnemyGun_BeforeExplode,
	BulletEnemyGun,

	EnemyRocket_Walking,
	EnemyRocket_Stand,
	EnemyRocket_Sitting,
	EnemyRocket_BeforeExplode,
	BulletEnemyRocket_Horizontal,
	BulletEnemyRocket_Cross,

	Item_Hide,
	Item_Bouncing,
	Item_Falling,
	Item_Grounding,
	Item_Disappearing,
	Capsule_Idle,
	Capsule_Openning,

	Ambush_NotYet,
	Ambush_Being,
	Ambush_HasDone,

	Explode,

	Shield_Side,
	Shield_Straight,
	Shield_Down,
	Shield_Up,

	Bunker_Idle_0,
	Bunker_Idle_1,
	Bunker_Idle_2,
	Bunker_Idle_3,
	Bunker_Idle_4,
	Bunker_Idle_5,
	Bunker_Idle_6,
	Bunker_Idle_7,
	Bunker_Spin  ,
	Bullet_Bunker,

	DoorDarkIdle      ,
	DoorDarkOpenning  ,
	DoorLightIdle     ,
	DoorLightOpenning ,

	BreakableLedge_Intact,
	BreakableLedge_Separated,

	MovingLedge_Moving,
	MovingLedge_Stop,
	MovingLedge_Stall, // stop by updater due to being out of viewport

	Captain_Standing,
	Captain_Walking,
	Captain_Jumping, // use vel to keep track if it's jumping or falling
	Captain_Falling,
	Captain_Kicking,
	Captain_Spinning,
	Captain_Throwing,
	Captain_Tackle,
	Captain_Punching,
	Captain_Sitting,
	Captain_SitPunching,
	Captain_CoverTop,
	Captain_CoverLow,
	Captain_FallToWater,
	Captain_InWater,
	Captain_Swimming,
	Captain_Climbing,
	Captain_Injured, // when being attacked at the side (left or right)
	Captain_Dead,
	CaptainElectricShock,


	EnemyWizard_Walking,
	EnemyWizard_Stand,
	EnemyWizard_BeforeDefeated,
	EnemyWizard_Defeated,
	EnemyWizard_Laught,
	EnemyWizard_FlyUp,
	EnemyWizard_FlyDown,
	EnemyWizard_Flying,
	EnemyWizard_ShootWhenFly,
	EnemyWizard_ShootBullet,
	EnemyWizard_ShootBulletFire,

	BulletFireEnemyWizard_Horizontal,
	BulletFireEnemyWizard_Vertical,
	BulletEnemyWizard_Horizontal,
	BulletEnemyWizard_SemiCross,
	BulletEnemyWizard_Cross,

	EnemyFly_Fly,
	EnemyFly_Falling,
	EnemyFly_Shoot,

	ElectricBat_Sleep,
	ElectricBat_StartFly,
	ElectricBat_EndFly,
	ElectricBat_FlyAttack,
	ElectricBat_Fly,

	BulletEnemyFly_Up,
	BulletEnemyFly_Down,
	BulletEnemyFly_Hor,
	BulletEnemyFly_CrossUp,
	BulletEnemyFly_CrossDown,

	DynamiteNapalm_FallFromTheSky,
	DynamiteNapalm_Standing,
	DynamiteNapalm_Intact_Running,
	DynamiteNapalm_ThrowDynamite,
	DynamiteNapalm_Intact_Shooting,
	DynamiteNapalm_Intact_Injure,

	DynamiteNapalm_Headless_Standing,
	DynamiteNapalm_Headless_Running_Shooting,
	DynamiteNapalm_BeforeExplode,
	DynamiteNapalm_FireBullet,
	DynamiteNapalm_Dynamite,

	ElectricTrap_Active,

	NotExist //Use to initialize
};

enum class Behaviors // for enemy, moving ledges
{
	EnemyGun_Shoot     = 0, 
	EnemyGun_ShootFast = 1, 
	EnemyGun_RunOnly   = 2, 
	EnemyGun_Ambush    = 3, 

	EnemyRocket_ShootStraight = 10, 
	EnemyRocket_ShootCross    = 11, 
	EnemyRocket_BackAndForth  = 12, 
	EnemyRocket_Ambush        = 13,

	EnemyFly_Stupid = 15,

	ElectricBat_Stupid = 17,

	EnemyWizard_FlyingShoot = 20,
	EnemyWizard_GroundShoot = 21,
	EnemyWizard_Jump = 22,
	EnemyWizard_FlyBackCorner = 23,
	EnemyWizard_RunToCap = 24,
	EnemyWizard_TurnOffLight = 25, 
	EnemyWizard_Laught = 26,

	DynamiteNapalm_Fall,
	DynamiteNapalm_Throw,
	DynamiteNapalm_Shoot,
	DynamiteNapalm_Run,
	DynamiteNapalm_AttackBeforeDead,

	MovingLedge_Horizontal = 40,
	MovingLedge_Diagonal = 41,
	MovingLedge_Circle = 42
};

enum class Scene
{
	Greeting,
	Charleston,
	BossCharleston,
	Pittsburgh,
	RedAlert, 
	Count
};




