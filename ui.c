#include "ponygame_nuklear.h"

static struct nk_font *mysteryquest;

void
pony_fonts(struct nk_font_atlas *atlas) {
	mysteryquest = nk_font_atlas_add_from_file(atlas, "fonts/mysteryquest/MysteryQuestRegular.ttf", 32, 0);
}

static nk_bool
transparent_begin(struct nk_context *ctx, const char *title, struct nk_rect r, enum nk_window_flags flags) {
	struct nk_style *s = &ctx->style;
	nk_style_push_color(ctx, &s->window.background, nk_rgba(0,0,0,0));
	nk_style_push_style_item(ctx, &s->window.fixed_background, nk_style_item_color(nk_rgba(0,0,0,0)));
	return nk_begin(ctx, title, r, flags);
		
	
}

static void
transparent_end(struct nk_context *ctx) {
	nk_end(ctx);
	nk_style_pop_color(ctx);
	nk_style_pop_style_item(ctx);
}

void
upgrade_menu(struct nk_context *ctx, int32_t win_width, int32_t win_height) {
	float width = 800;
	float height = 600;

	float x = (win_width - width) / 2.0;
	float y = (win_height - height) / 2.0;

	if(nk_begin(ctx, "Choose An Upgrade!!!", nk_rect(x, y, width, height), NK_WINDOW_TITLE)) {
		//nk_layout_row_static(ctx, 30, width / 4, 3);
		nk_layout_row_dynamic(ctx, 30, 3);
		nk_button_label(ctx, "Extra Arrows");
		nk_button_label(ctx, "Faster Movement");
		nk_button_label(ctx, "Cooler Pony");
	}
	nk_end(ctx);
}

void pony_ui(struct nk_context *ctx, int32_t width, int32_t height) {
	nk_style_set_font(ctx, &mysteryquest->handle);
	/*if(transparent_begin(ctx, "ui", nk_rect(0, 0, width, height), 0)) {
		nk_layout_row_static(ctx, 20, width / 2, 2);
		nk_label(ctx, "Hello world", NK_TEXT_LEFT);
		nk_button_label(ctx, "test button");
	}
	transparent_end(ctx);*/

	upgrade_menu(ctx, width, height);
}