@type Enemy : Sprite
	Ref(struct Arrow) arrow_tracker[4];
	int arrow_track_next;
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

	#define ENEMY_ARROW_TRACK_COUNT 4

	#define ENEMY_PAPER 0 /* First enemy type */

	extern Enemy *enemy_new_with_type(int type);

@tree
	self : Enemy
		sprite_play($, &res.enemy.enemy1_tex.loop)