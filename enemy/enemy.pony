@type Enemy : Sprite
	vec2 velocity;
	float walk_anim_t;
	int health;

	int type;

	SpatialHashRef ref;

@construct
@tick
@destruct

@header
	extern SpatialHash enemy_hash;

	#define ENEMY_PAPER 0 /* First enemy type */

	extern Enemy *enemy_new_with_type(int type);

@tree
	self : Enemy
		sprite_play($, &res.enemy.enemy1_tex.loop)