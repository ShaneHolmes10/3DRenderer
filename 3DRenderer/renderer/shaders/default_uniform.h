#pragma once

/**
 * @brief Default uniform for programs that need no per-draw shader
 * data.
 *
 * The camera handles the view and model transforms internally, so the
 * vertex shader receives vertices already in camera space. No matrices
 * are needed here.
 */
struct DefaultUniform {};
