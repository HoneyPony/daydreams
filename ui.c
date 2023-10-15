#include "ponygame_nuklear.h"

#include "my.ponygame.h"

static void
game_style(struct nk_context *ctx)
{
	struct nk_color table[NK_COLOR_COUNT];
	int pr = (int)(player->tree.sprite->r * 255);
	int pg = (int)(player->tree.sprite->g * 255);
	int pb = (int)(player->tree.sprite->b * 255);
	struct nk_color pcolor = nk_rgba(pr, pg, pb, 255);
    table[NK_COLOR_TEXT] = pcolor;
	table[NK_COLOR_WINDOW] = nk_rgba(220, 220, 220, 255);
	table[NK_COLOR_HEADER] = nk_rgba(220, 220, 220, 255);
	table[NK_COLOR_BORDER] = pcolor;
	table[NK_COLOR_BUTTON] = nk_rgba(230, 230, 230, 255);
	table[NK_COLOR_BUTTON_HOVER] = nk_rgba(240, 240, 240, 255);
	table[NK_COLOR_BUTTON_ACTIVE] = nk_rgba(210, 210, 210, 255);
	table[NK_COLOR_TOGGLE] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_TOGGLE_HOVER] = nk_rgba(45, 53, 56, 255);
	table[NK_COLOR_TOGGLE_CURSOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SELECT] = nk_rgba(57, 67, 61, 255);
	table[NK_COLOR_SELECT_ACTIVE] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SLIDER] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_SLIDER_CURSOR] = nk_rgba(48, 83, 111, 245);
	table[NK_COLOR_SLIDER_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
	table[NK_COLOR_SLIDER_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
	table[NK_COLOR_PROPERTY] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_EDIT] = nk_rgba(50, 58, 61, 225);
	table[NK_COLOR_EDIT_CURSOR] = nk_rgba(210, 210, 210, 255);
	table[NK_COLOR_COMBO] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_CHART] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_CHART_COLOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_CHART_COLOR_HIGHLIGHT] = nk_rgba(255, 0, 0, 255);
	table[NK_COLOR_SCROLLBAR] = nk_rgba(50, 58, 61, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR] = nk_rgba(48, 83, 111, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_HOVER] = nk_rgba(53, 88, 116, 255);
	table[NK_COLOR_SCROLLBAR_CURSOR_ACTIVE] = nk_rgba(58, 93, 121, 255);
	table[NK_COLOR_TAB_HEADER] = nk_rgba(48, 83, 111, 255);
	nk_style_from_table(ctx, table);

	struct nk_style *s = &ctx->style;
	s->window.border = 30;

	s->button.border = 2;
}

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

	const char *desc_text = NULL;

	if(nk_begin(ctx, "Choose An Upgrade!!!", nk_rect(x, y, width, height), NK_WINDOW_TITLE | NK_WINDOW_NO_SCROLLBAR)) {
		//nk_layout_row_static(ctx, 30, width / 4, 3);
		nk_layout_row_dynamic(ctx, 60, 3);
		if(nk_widget_is_hovered(ctx)) desc_text = "More arrows";
		nk_button_label(ctx, "Extra Arrows");

		if(nk_widget_is_hovered(ctx)) desc_text = "You move the faster";
		nk_button_label(ctx, "Faster Movement");

		if(nk_widget_is_hovered(ctx)) desc_text = "Your pony is cooler";
		nk_button_label(ctx, "Cooler Pony");

		if(desc_text) {
			nk_layout_row_dynamic(ctx, 400, 1);
			nk_label_wrap(ctx, desc_text);
		}
		
	}
	nk_end(ctx);
}

void pony_ui(struct nk_context *ctx, int32_t width, int32_t height) {
	nk_style_set_font(ctx, &mysteryquest->handle);
	game_style(ctx);
	/*if(transparent_begin(ctx, "ui", nk_rect(0, 0, width, height), 0)) {
		nk_layout_row_static(ctx, 20, width / 2, 2);
		nk_label(ctx, "Hello world", NK_TEXT_LEFT);
		nk_button_label(ctx, "test button");
	}
	transparent_end(ctx);*/

	upgrade_menu(ctx, width, height);
}