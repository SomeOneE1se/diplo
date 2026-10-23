#ifndef SETTINGS_H
#define SETTINGS_H

/* renderer params  */
#define OPEN_GL_MAJOR 4
#define OPEN_GL_MINOR 6

/* orto projection  */
#if 1
#    define ORTO_LEFT  -180
#    define ORTO_RIGHT 180
#    define ORTO_TOP   90
#    define ORTO_BOT   -90
#else
#    define ORTO_LEFT  (-(WND_WIDTH / 2))
#    define ORTO_RIGHT (WND_WIDTH / 2)
#    define ORTO_TOP   (WND_HEIGHT / 2)
#    define ORTO_BOT   (-(WND_HEIGHT / 2))
#endif
#define ORTO_NEAR -1.0
#define ORTO_FAR  1.0

/* window init params   */
#define WND_WIDTH     1400
#define WND_HEIGHT    700
#define WND_NAME      "sim"
#define WND_RESIZABLE 1
#define WND_VERT_SYNC 1

/* default shaders  */
#define DEFAULT_VERTEX   "shaders/default_vertex.glsl"
#define DEFAULT_FRAGMENT "shaders/default_fragment.glsl"

/* default texture  */
#define DEFAULT_TEXTURE "textures/texture1.png"

#endif  // SETTINGS_H
