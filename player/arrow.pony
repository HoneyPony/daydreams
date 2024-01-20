@type Arrow : Sprite
	vec2 velocity;
	float lifetime;

	int type;
	int hits; /* Used for piercing */

	SpatialHashRef ref;

@construct
@tick
@destruct

@header
	//void arrow_spawn(Player *parent, int type);
	Arrow *arrow_new_type(int type);
	extern SpatialHash arrow_hash;

	void arrow_hit(Arrow *ar);

	#define ARROW_STAR 0

@tree
	self : Arrow
		sprite_play($, &res.player.arrow_spawn_tex.loop)