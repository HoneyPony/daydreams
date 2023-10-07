@type Enemy : Sprite
	vec2 velocity;
	float walk_anim_t;
	int health;

	SpatialHashRef ref;

@construct
@tick
@destruct

@header
	extern SpatialHash enemy_hash;

@tree
	self : Enemy
		sprite_play($, &res.enemy.enemy1_tex.loop)