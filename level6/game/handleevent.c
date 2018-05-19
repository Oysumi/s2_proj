#include "../headers/struct.h"
#include "../headers/const.h"

void HandleEvent ( input_t * inkey, bubble_t * bub )
{
	SDL_Event event ;

	while ( SDL_PollEvent ( &event ) )
	{
		switch ( event.type )
		{
			case SDL_KEYDOWN :
				inkey->key[event.key.keysym.sym] = 1 ;
				if ( event.key.keysym.sym == SDLK_SPACE )
				{
					bub->launched = 1 ;
				}
				break ;
			case SDL_KEYUP :
				inkey->key[event.key.keysym.sym] = 0 ;
				break ;
			case SDL_QUIT :
				inkey->quit = 1 ;
				break ;
			default :
				break ;
		}
	}

}

bool escape ( input_t * inkey )
{
  if ( inkey->quit || inkey->key[SDLK_ESCAPE] || inkey->key[SDLK_q] )
  {
    return true ;
  }
  return false ;
}