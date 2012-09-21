#pragma once

#define TUXIS_EXPORTING

#ifdef TUXIS_EXPORTING
#define TUXIS_DECLSPEC __declspec(dllexport)
#else
#define TUXIS_DECLSPEC __declspec(dllimport)
#endif