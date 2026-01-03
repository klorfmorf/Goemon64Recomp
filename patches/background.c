#include "patches.h"

typedef struct graphics_node {
	struct graphics_node *next;
	u8 flags;
	u8 unk_8;
	s16 priority;
} GraphicsNode;

typedef struct background_graphics_node {
	GraphicsNode node;
	u8 unk_8[4];
	s16 overlay_file_id;
	u16 flags;
	s16 texture_width;
	s16 texture_height;
	f32 start_x;
	f32 start_y;
	f32 upper_left_corner_x;
	f32 upper_left_corner_y;
	f32 rectangle_width;
	f32 rectangle_height;
	u8 alpha;
	u8 unk_2d;
	s16 unk_2e;
	s16 unk_30;
	s16 unk_32;
	s16 unk_34;
	u8 unk_36;
	u8 unk_37;
	u8 *texture_data;
	u8 *palette_data;
	u16 bits_per_pixel;
} BackgroundGraphicsNode;

void func_80022A74_23674(BackgroundGraphicsNode *node);
void func_80022214_22E14(BackgroundGraphicsNode *node);
void func_80021894_22494(u8 *texture_data, u8 *palette_data, f32 start_x, f32 start_y);

RECOMP_PATCH void func_80021740_22340(BackgroundGraphicsNode* node) {
	s32 image_size;

	if (!(node->flags & (1 << 13))) {
		gSPSegment(D_8015C5CC_15D1CC++, 8, func_800141C4_14DC4(node->overlay_file_id));
		node->texture_data = (u8 *)0x08000000;
	}

	if (node->texture_data == (u8 *)-1) {
		// Intentionally crash by writing to an invalid memory location, triggering the debugger.
		*((volatile s32 *)-1) = 0;
	}

	if (node->flags & (1 << 2)) {
		node->bits_per_pixel = 4;
	} else if (node->flags & (1 << 3)) {
		node->bits_per_pixel = 8;
	} else {
		node->bits_per_pixel = 16;
	}

	if (!(node->flags & (1 << 13))) {
		image_size = node->texture_width * node->texture_height * node->bits_per_pixel;
		if (image_size < 0) {
			image_size += 7;
		}

		node->palette_data = node->texture_data + (image_size >> 3);
	}

	if (node->flags & (1 << 14)) {
		func_80022214_22E14(node);
	} else if (node->flags & (1 << 15)) {
		func_80021894_22494(node->texture_data, node->palette_data, node->start_x, node->start_y);
	} else {
		func_80022A74_23674(node);
	}
}

extern s32 D_8006D158_6DD58;
extern s32 D_8006D15C_6DD5C;
extern s32 D_8006D160_6DD60; // g_background_width
extern s32 D_8006D164_6DD64; // g_background_height

void func_80021B98_22798(u8 *texture_data, f32 source_x, f32 source_y, s32 tile_width, s32 tile_height, u32 destination_x, u32 destination_y);

RECOMP_PATCH void func_80021894_22494(u8 *texture_data, u8 *palette_data, f32 start_x, f32 start_y) {
	s32 source_x;
	s32 source_y;
	s32 destination_x;
	s32 destination_y;
	s32 tile_width;
	s32 tile_height;
	f32 x_remainder;

	x_remainder = start_x - (f32)(s32)start_x;

	if (start_x < 0.0) {
		start_x = start_x + (f32)(-(s32)start_x / 1280 + 1) * 1280.0 + x_remainder;
	}

	if (1280.0 <= start_x) {
		start_x = (f32)((s32)start_x % 1280) + x_remainder;
	}

	if (start_y > 240.0) {
		start_y = 240.0;
	} else if (start_y < 0.0) {
		start_y = 0.0;
	}

	gDPLoadTLUT_pal256(D_8015C5CC_15D1CC++, palette_data);

	start_x /= 2.0f;
	start_y /= 2.0f;

	// Loop over the screen vertically, drawing a row of tiles in each iteration.
	for (destination_y = D_8006D15C_6DD5C; destination_y < D_8006D164_6DD64; destination_y += 20) {
		source_y = (s32)start_y;

		// If we're near the bottom edge, calculate a partial tile height.
		if (D_8006D164_6DD64 - 24 < destination_y) {
			tile_height = (D_8006D164_6DD64 - destination_y + 1);
			if (tile_height < 0) {
				tile_height++;
			}
			tile_height /= 2;
		} else {
			// Otherwise, use the standard full height for a tile.
			tile_height = 12;
		}

		// Reset the horizontal source coordinate at the start of each new row.
		source_x = (s32)start_x;

		// Loop over the screen horizontally, drawing each tile in the current row.
		for (destination_x = D_8006D158_6DD58; destination_x < D_8006D160_6DD60; destination_x += 326) {
			// If we're near the right edge, calculate a partial tile width.
			if (D_8006D160_6DD60 - 328 < destination_x) {
				tile_width = (D_8006D160_6DD60 - destination_x + 1);
				if (tile_width < 0) {
					tile_width++;
				}
				tile_width /= 2;
			} else {
				// Otherwise, use the standard full width for a tile.
				tile_width = 164;
			}

			// Draw the calculated tile.
			func_80021B98_22798(texture_data, source_x, source_y, tile_width, tile_height, destination_x, destination_y);

			// Advance the source X coordinate for the next tile in this row.
			source_x += (tile_width - 1);
		}

		// Advance the source Y coordinate for the next row of tiles.
		start_y += 10.0f;
	}
}

RECOMP_PATCH void func_80021B98_22798(u8 *texture_data, f32 source_x, f32 source_y, s32 tile_width, s32 tile_height, u32 destination_x, u32 destination_y)
{
	// Check if the destination rectangle wraps around the screen edge
	if (640 < (destination_x + tile_width * 2)) {
		// First part: Draw the wrapped portion (right side of tile -> left side of screen).
		s32 wrap_width;
		s32 right_width;

		wrap_width = (destination_x + tile_width * 2) - 640;
		right_width = tile_width * 2 - wrap_width;

		// Load the right part of the source tile.
		gDPSetTextureImage(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, 640, texture_data);
		gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, (right_width / 2 + 7) / 8, 0, G_TX_LOADTILE, 8, G_TX_CLAMP, 0, 0, G_TX_NOMIRROR, 0, 0);
		gDPLoadSync(D_8015C5CC_15D1CC++);
		gDPLoadTile(D_8015C5CC_15D1CC++, G_TX_LOADTILE, 
			(s32)source_x << 2, 
			(s32)source_y << 2, 
			((s32)source_x + right_width / 2 - 1) << 2, 
			((s32)source_y + tile_height - 1) << 2);
		gDPPipeSync(D_8015C5CC_15D1CC++);
		gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, (right_width / 2 + 7) / 8, 0, G_TX_RENDERTILE, 8, G_TX_CLAMP, 0, 0, G_TX_NOMIRROR, 0, 0);
		gDPSetTileSize(D_8015C5CC_15D1CC++, G_TX_RENDERTILE, 
			(s32)source_x << 2, 
			(s32)source_y << 2, 
			((s32)source_x + right_width / 2 - 1) << 2, 
			((s32)source_y + tile_height - 1) << 2);

		// Draw the rectangle on the right edge of the screen.
		gSPTextureRectangle(D_8015C5CC_15D1CC++, 
			destination_x << 2, 
			destination_y << 2, 
			(destination_x + right_width - 1) << 2, 
			(destination_y + tile_height * 2 - 1) << 2, 
			G_TX_RENDERTILE, 
			(s32)(source_x * 32.0f), 
			(s32)(source_y * 32.0f), 
			1 << 9, // dsdx = 0.5
			1 << 9  // dtdy = 0.5
		);

		// Second part: Draw the non-wrapped portion (left side of tile -> right side of screen).

		// Load the left part of the source tile.
		gDPSetTextureImage(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, 640, texture_data);
		gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, (wrap_width / 2 + 7) / 8, 0, G_TX_LOADTILE, 8, G_TX_CLAMP, 0, 0, G_TX_NOMIRROR, 0, 0);
		gDPLoadSync(D_8015C5CC_15D1CC++);
		gDPLoadTile(D_8015C5CC_15D1CC++, G_TX_LOADTILE, 
			((s32)source_x + right_width / 2) << 2, 
			(s32)source_y << 2, 
			((s32)source_x + tile_width - 1) << 2, 
			((s32)source_y + tile_height - 1) << 2);
		gDPPipeSync(D_8015C5CC_15D1CC++);
		gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_CI, G_IM_SIZ_8b, (wrap_width / 2 + 7) / 8, 0, G_TX_RENDERTILE, 8, G_TX_CLAMP, 0, 0, G_TX_NOMIRROR, 0, 0);
		gDPSetTileSize(D_8015C5CC_15D1CC++, G_TX_RENDERTILE, 
			((s32)source_x + right_width / 2) << 2, 
			(s32)source_y << 2, 
			((s32)source_x + tile_width - 1) << 2, 
			((s32)source_y + tile_height - 1) << 2);

		// Draw the rectangle on the left edge of the screen.
		gSPTextureRectangle(D_8015C5CC_15D1CC++, 
			0, 
			destination_y << 2, 
			(wrap_width - 1) << 2, 
			(destination_y + tile_height * 2 - 1) << 2, 
			G_TX_RENDERTILE, 
			(s32)((source_x + right_width / 2) * 32.0f), 
			(s32)(source_y * 32.0f), 
			1 << 9, // dsdx = 0.5
			1 << 9  // dtdy = 0.5
		);
	} else {
		// Simple case: Draw the entire tile in one go.

		// Load the tile from the source texture.
		gDPLoadTextureTile(
			D_8015C5CC_15D1CC++, 
			texture_data, 
			G_IM_FMT_CI, 
			G_IM_SIZ_8b, 
			640, 0, 
			(s32)source_x, (s32)source_y, 
			((s32)source_x + tile_width - 1), ((s32)source_y + tile_height - 1), 
			0, 
			G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);

		// Draw the textured rectangle, scaled 2x.
		gSPTextureRectangle(D_8015C5CC_15D1CC++, 
			destination_x << 2, 
			destination_y << 2, 
			(destination_x + tile_width * 2 - 1) << 2, 
			(destination_y + tile_height * 2 - 1) << 2, 
			G_TX_RENDERTILE, 
			(s32)(source_x * 32.0f), 
			(s32)(source_y * 32.0f), 
			1 << 9, // dsdx = 0.5 (0x200 in S5.10)
			1 << 9  // dtdy = 0.5 (0x200 in S5.10)
		);
	}
}

void func_80022EC0_23AC0(BackgroundGraphicsNode *node);
void func_80022348_22F48(s32 destination_x, s32 destination_y, s32 source_x, s32 source_y, s32 width, s32 height, BackgroundGraphicsNode *node);

RECOMP_PATCH void func_80022214_22E14(BackgroundGraphicsNode *node) {
	s32 destination_x;
	s32 destination_y_start;
	s32 source_x;
	s32 source_y;
	s32 tile_width;
	s32 total_height;
	s32 bottom_edge;
	s32 maximum_tile_height;
	s32 current_destination_y;

	// Initialize rendering coordinates from the node properties.
	destination_x = (s32)node->upper_left_corner_x;
	destination_y_start = (s32)node->upper_left_corner_y;
	source_x = (s32)node->start_x;
	source_y = (s32)node->start_y;
	tile_width = (s32)node->rectangle_width;
	total_height = (s32)node->rectangle_height;

	bottom_edge = destination_y_start + total_height;

	// This calculates the maximum height of a tile that can be loaded at once,
	// based on its width.
	maximum_tile_height = (s32)(2048.0f / tile_width);

	// This function sets up texture and rendering modes.
	func_80022EC0_23AC0(node);

	// Loop vertically from the top of the rectangle to the bottom, drawing one tile per iteration.
	for (current_destination_y = destination_y_start; current_destination_y < bottom_edge; ) {
		s32 current_tile_height;

		// Determine the height of the tile for this iteration.
		current_tile_height = maximum_tile_height;

		// If drawing a full-height tile would go past the bottom edge,
		// clamp the tile height to the remaining vertical space.
		if (current_destination_y + current_tile_height > bottom_edge) {
			current_tile_height = bottom_edge - current_destination_y;
		}

		// Draw the calculated tile segment.
		func_80022348_22F48(destination_x, current_destination_y, source_x, source_y, tile_width, current_tile_height, node);

		// Advance the destination and source Y coordinates for the next tile.
		current_destination_y += current_tile_height;
		source_y += current_tile_height;
	}
}

void func_80022500_23100(u32 destination_x, u32 destination_y, s32 source_x, s32 source_y, s32 rectangle_width, s32 rectangle_height, BackgroundGraphicsNode *node);

RECOMP_PATCH void func_80022348_22F48(s32 destination_x, s32 destination_y, s32 source_x, s32 source_y, s32 width, s32 height, BackgroundGraphicsNode *node)
{
	s32 clip_x0;
	s32 clip_y0;
	s32 clip_x1;
	s32 clip_y1;

	// This ensures that source coordinates always fall within the texture's bounds.
	if (node->texture_width > 0) {
		source_x %= node->texture_width;
		if (source_x < 0) {
			source_x += node->texture_width;
		}
	}

	if (node->texture_height > 0) {
		source_y %= node->texture_height;
		if (source_y < 0) {
			source_y += node->texture_height;
		}
	}

	// Define the clipping rectangle (also known as a scissor rectangle).
	clip_x0 = node->unk_2e;
	clip_y0 = node->unk_30;
	clip_x1 = node->unk_32;
	clip_y1 = node->unk_34;

	// --- Perform Clipping ---

	// Clip against the left edge.
	if (destination_x < clip_x0) {
		s32 difference = clip_x0 - destination_x;
		width -= difference;
		source_x += difference;
		destination_x = clip_x0;
	}

	// Clip against the top edge.
	if (destination_y < clip_y0) {
		s32 difference = clip_y0 - destination_y;
		height -= difference;
		source_y += difference;
		destination_y = clip_y0;
	}

	// Clip against the right edge.
	if (destination_x + width > clip_x1) {
		width = clip_x1 - destination_x;
	}

	// Clip against the bottom edge.
	if (destination_y + height > clip_y1) {
		height = clip_y1 - destination_y;
	}

	// After clipping, if the tile has no width or height, there's nothing to draw.
	if (width > 0 && height > 0) {
		// Call the actual low-level drawing function with the wrapped and clipped parameters.
		func_80022500_23100(destination_x, destination_y, source_x, source_y, width, height, node);
	}
}

RECOMP_PATCH void func_80022500_23100(u32 destination_x, u32 destination_y, s32 source_x, s32 source_y, s32 rectangle_width, s32 rectangle_height, BackgroundGraphicsNode *node) {
	s32 image_format;

	if (node->flags & (1 << 0)) {
		image_format = G_IM_FMT_CI;
	} else if (node->flags & (1 << 1)) {
		image_format = G_IM_FMT_IA;
	} else {
		image_format = G_IM_FMT_RGBA;
	}

	if (node->flags & (1 << 2)) {
		gDPLoadTextureTile_4b(
			D_8015C5CC_15D1CC++, 
			node->texture_data, 
			G_IM_FMT_CI,
			node->texture_width, node->texture_height, 
			source_x, source_y, 
			(source_x + rectangle_width - 1), (source_y + rectangle_height - 1), 
			0, 
			G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
	} else if (node->flags & (1 << 3)) {
		gDPLoadTextureTile(
			D_8015C5CC_15D1CC++, 
			node->texture_data, 
			image_format, 
			G_IM_SIZ_8b, 
			node->texture_width, node->texture_height, 
			source_x, source_y, 
			(source_x + rectangle_width - 1), (source_y + rectangle_height - 1), 
			0, 
			G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
	} else {
		gDPLoadTextureTile(
			D_8015C5CC_15D1CC++, 
			node->texture_data, 
			G_IM_FMT_RGBA, 
			G_IM_SIZ_16b, 
			node->texture_width, node->texture_height, 
			source_x, source_y, 
			(source_x + rectangle_width - 1), (source_y + rectangle_height - 1), 
			0, 
			G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, 
			G_TX_NOMASK, G_TX_NOMASK, 
			G_TX_NOLOD, G_TX_NOLOD
		);
	}

	gSPTextureRectangle(
		D_8015C5CC_15D1CC++, 
		destination_x << 2, destination_y << 2, 
		(destination_x + rectangle_width) << 2, (destination_y + rectangle_height) << 2, 
		G_TX_RENDERTILE, 
		source_x << 5, source_y << 5, 
		1 << 10, 1 << 10
	);
}

void func_80022DF4_239F4(u32 destination_x, u32 destination_y, s32 source_x, s32 source_y, s32 rectangle_width, s32 rectangle_height, BackgroundGraphicsNode *node);

RECOMP_PATCH void func_80022A74_23674(BackgroundGraphicsNode *node) {
	s32 dest_x = (s32)node->upper_left_corner_x;
	s32 dest_y = (s32)node->upper_left_corner_y;
	s32 src_x = (s32)node->start_x;
	s32 src_y = (s32)node->start_y;
	s32 width = (s32)node->rectangle_width;
	s32 height = (s32)node->rectangle_height;
	s32 max_tile_height;
	s32 height_remaining;
	s32 current_dest_y;
	s32 current_src_y;

	// The original code would trap on division by zero. We prevent it.
	if (width <= 0 || node->texture_width <= 0 || node->texture_height <= 0) {
		return;
	}

	// Calculate the maximum height of a tile that can be loaded into TMEM (2KB in this case).
	max_tile_height = 2048 / width;
	if (max_tile_height <= 0) {
		max_tile_height = 1; // Ensure at least one row can be processed.
	}

	// Wrap source X coordinate for tiling textures.
	src_x %= node->texture_width;
	if (src_x < 0) {
		src_x += node->texture_width;
	}

	// Wrap source Y coordinate for tiling textures.
	src_y %= node->texture_height;
	if (src_y < 0) {
		src_y += node->texture_height;
	}

	// Set up the RDP rendering state.
	func_80022EC0_23AC0(node);

	height_remaining = height;
	current_dest_y = dest_y;
	current_src_y = src_y;

	// Loop until the entire rectangle height has been drawn.
	while (height_remaining > 0) {
		// Determine the height of the current tile. It's the minimum of:
		// 1. The total height left to draw.
		// 2. The maximum tile height allowed by TMEM.
		// 3. The vertical distance from the current source Y to the texture's bottom edge.
		s32 tile_height = height_remaining;
		if (tile_height > max_tile_height) {
			tile_height = max_tile_height;
		}

		s32 height_before_wrap = node->texture_height - current_src_y;
		if (tile_height > height_before_wrap) {
			tile_height = height_before_wrap;
		}

		// If we are at the texture edge and can't draw anything, wrap src_y and restart the loop.
		if (tile_height <= 0) {
			current_src_y = 0;
			continue;
		}

		// Draw the tile. func_80022DF4_239F4 handles horizontal (X-axis) wrapping.
		func_80022DF4_239F4(dest_x, current_dest_y, src_x, current_src_y, width, tile_height, node);

		// Update state for the next iteration.
		height_remaining -= tile_height;
		current_dest_y += tile_height;
		current_src_y += tile_height;

		// If we've reached the bottom of the source texture, wrap back to the top.
		if (current_src_y >= node->texture_height) {
			current_src_y = 0;
		}
	}
}


RECOMP_PATCH void func_80022DF4_239F4(u32 destination_x, u32 destination_y, s32 source_x, s32 source_y, s32 rectangle_width, s32 rectangle_height, BackgroundGraphicsNode *node) {
	if (source_x + rectangle_width > node->texture_width) {
		s32 first_part_width;
		s32 second_part_width;

		first_part_width = node->texture_width - source_x;
		func_80022500_23100(destination_x, destination_y, source_x, source_y, first_part_width, rectangle_height, node);

		second_part_width = rectangle_width - first_part_width;
		func_80022500_23100(destination_x + first_part_width, destination_y, 0, source_y, second_part_width, rectangle_height, node);
	} else {
		func_80022500_23100(destination_x, destination_y, source_x, source_y, rectangle_width, rectangle_height, node);
	}
}

extern Gfx D_8006D0F0_6DCF0[];

#define G_CC_CUSTOM_1 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE
#define G_CC_CUSTOM_2 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0

RECOMP_PATCH void func_80022EC0_23AC0(BackgroundGraphicsNode *node) {
	gSPDisplayList(D_8015C5CC_15D1CC++, &D_8006D0F0_6DCF0);

	if (node->flags & (1 << 4)) {
		gDPSetPrimColor(D_8015C5CC_15D1CC++, 0, 0, 255, 255, 255, node->alpha);
		gDPSetRenderMode(D_8015C5CC_15D1CC++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

		if (node->flags & (1 << 5)) {
			gDPSetCombineMode(D_8015C5CC_15D1CC++, G_CC_CUSTOM_2, G_CC_CUSTOM_2);
			gDPSetAlphaCompare(D_8015C5CC_15D1CC++, G_AC_THRESHOLD);
			gDPSetBlendColor(D_8015C5CC_15D1CC++, 0, 0, 0, 1);
		} else {
			gDPSetCombineMode(D_8015C5CC_15D1CC++, G_CC_CUSTOM_1, G_CC_CUSTOM_1);
		}
	} else {
		if (node->flags & (1 << 5)) {
			gDPSetRenderMode(D_8015C5CC_15D1CC++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
			gDPSetAlphaCompare(D_8015C5CC_15D1CC++, G_AC_THRESHOLD);
			gDPSetBlendColor(D_8015C5CC_15D1CC++, 0, 0, 0, 1);
		}
	}

	// @recomp Point filtering removed (looks better in basically all cases, especially when stretched). G_TF_BILERP is set in previous gSPDisplayList call.
	// gDPSetTextureFilter(D_8015C5CC_15D1CC++, G_TF_POINT);

	if (node->flags & (1 << 0)) {
		if (node->flags & (1 << 3)) {
			gDPSetTextureImage(D_8015C5CC_15D1CC++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, node->palette_data);
			gDPTileSync(D_8015C5CC_15D1CC++);
			gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 256, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
			gDPLoadSync(D_8015C5CC_15D1CC++);
			gDPLoadTLUTCmd(D_8015C5CC_15D1CC++, G_TX_LOADTILE, 255);
			gDPPipeSync(D_8015C5CC_15D1CC++);
		} else {
			gDPSetTextureImage(D_8015C5CC_15D1CC++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, node->palette_data);
			gDPTileSync(D_8015C5CC_15D1CC++);
			gDPSetTile(D_8015C5CC_15D1CC++, G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 256, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);
			gDPLoadSync(D_8015C5CC_15D1CC++);
			gDPLoadTLUTCmd(D_8015C5CC_15D1CC++, G_TX_LOADTILE, 15);
			gDPPipeSync(D_8015C5CC_15D1CC++);
		}
	} else {
		gDPSetTextureLUT(D_8015C5CC_15D1CC++, G_TT_NONE);
	}
}