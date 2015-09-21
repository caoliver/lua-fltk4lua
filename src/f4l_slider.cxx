#include "fltk4lua.hxx"
#include "f4l_slider.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>

namespace {

#define TYPE_LIST( _ ) \
  _( "FL_VERTICAL", FL_VERTICAL ) \
  _( "FL_HORIZONTAL", FL_HORIZONTAL ) \
  _( "FL_VERT_FILL_SLIDER", FL_VERT_FILL_SLIDER ) \
  _( "FL_HOR_FILL_SLIDER", FL_HOR_FILL_SLIDER ) \
  _( "FL_VERT_NICE_SLIDER", FL_VERT_NICE_SLIDER ) \
  _( "FL_HOR_NICE_SLIDER", FL_HOR_NICE_SLIDER )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, slider )


  inline Fl_Slider* check_slider( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SLIDER_NAME );
    return static_cast< Fl_Slider* >( p );
  }

  inline Fl_Scrollbar* check_scrollbar( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SCROLLBAR_NAME );
    return static_cast< Fl_Scrollbar* >( p );
  }

  inline Fl_Value_Slider* check_value_slider( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_VALUE_SLIDER_NAME );
    return static_cast< Fl_Value_Slider* >( p );
  }

  int slider_index( lua_State* L ) {
    Fl_Slider* s = check_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_slider_index_( L, s, key, n ) &&
          !f4l_valuator_index_( L, s, key, n ) &&
          !f4l_widget_index_( L, s, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int slider_newindex( lua_State* L ) {
    Fl_Slider* s = check_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_slider_newindex_( L, s, key, n ) ||
             f4l_valuator_newindex_( L, s, key, n ) ||
             f4l_widget_newindex_( L, s, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int scrollbar_index_( lua_State* L, Fl_Scrollbar* s,
                        char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushinteger( L, s->value() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "linesize", 8 ) == 0 ) {
          lua_pushinteger( L, s->linesize() );
          return 1;
        }
        break;
    }
    return 0;
  }

  int scrollbar_newindex_( lua_State* L, Fl_Scrollbar* s,
                           char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          s->value( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "linesize", 8 ) == 0 ) {
          s->linesize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
    }
    return 0;
  }

  int scrollbar_index( lua_State* L ) {
    Fl_Scrollbar* s = check_scrollbar( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !scrollbar_index_( L, s, key, n ) &&
          !f4l_slider_index_( L, s, key, n ) &&
          !f4l_valuator_index_( L, s, key, n ) &&
          !f4l_widget_index_( L, s, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int scrollbar_newindex( lua_State* L ) {
    Fl_Scrollbar* s = check_scrollbar( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(scrollbar_newindex_( L, s, key, n ) ||
             f4l_slider_newindex_( L, s, key, n ) ||
             f4l_valuator_newindex_( L, s, key, n ) ||
             f4l_widget_newindex_( L, s, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int scrollbar_setvalue( lua_State* L ) {
    Fl_Scrollbar* s = check_scrollbar( L, 1 );
    int pos = moon_checkint( L, 2, 0, INT_MAX );
    int ws = moon_checkint( L, 3, 0, INT_MAX );
    int f = moon_checkint( L, 4, 0, INT_MAX );
    int t = moon_checkint( L, 5, 0, INT_MAX );
    F4L_TRY {
      s->value( pos, ws, f, t );
    } F4L_CATCH( L );
    return 0;
  }

  int value_slider_index_( lua_State* L, Fl_Value_Slider* vs,
                           char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, vs->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, vs->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, vs->textcolor() );
          return 1;
        }
        break;
    }
    return 0;
  }

  int value_slider_newindex_( lua_State* L, Fl_Value_Slider* vs,
                              char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          vs->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          vs->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          vs->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

  int value_slider_index( lua_State* L ) {
    Fl_Value_Slider* vs = check_value_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !value_slider_index_( L, vs, key, n ) &&
          !f4l_slider_index_( L, vs, key, n ) &&
          !f4l_valuator_index_( L, vs, key, n ) &&
          !f4l_widget_index_( L, vs, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int value_slider_newindex( lua_State* L ) {
    Fl_Value_Slider* vs = check_value_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(value_slider_newindex_( L, vs, key, n ) ||
             f4l_slider_newindex_( L, vs, key, n ) ||
             f4l_valuator_newindex_( L, vs, key, n ) ||
             f4l_widget_newindex_( L, vs, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_slider( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Slider >( L, F4L_SLIDER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_scrollbar( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Scrollbar >( L, F4L_SCROLLBAR_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_value_slider( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Value_Slider >( L, F4L_VALUE_SLIDER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL int f4l_slider_index_( lua_State* L, Fl_Slider* s,
                                  char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        f4l_push_type_slider( L, s->type() );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "slider", 6 ) == 0 ) {
        f4l_push_boxtype( L, s->slider() );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "slider_size", 11 ) == 0 ) {
        lua_pushnumber( L, s->slider_size() );
        return 1;
      }
      break;
  }
  return 0;
}

MOON_LOCAL int f4l_slider_newindex_( lua_State* L, Fl_Slider* s,
                                     char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        s->type( f4l_check_type_slider( L, 3 ) );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "slider", 6 ) == 0 ) {
        s->slider( f4l_check_boxtype( L, 3 ) );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "slider_size", 11 ) == 0 ) {
        s->slider_size( luaL_checknumber( L, 3 ) );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_slider_bounds( lua_State* L ) {
  Fl_Slider* s = check_slider( L, 1 );
  double a = luaL_checknumber( L, 2 );
  double b = luaL_checknumber( L, 3 );
  F4L_TRY {
    s->bounds( a, b );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_slider_scrollvalue( lua_State* L ) {
  Fl_Slider* s = check_slider( L, 1 );
  int p = moon_checkint( L, 2, 0, INT_MAX );
  int sz = moon_checkint( L, 3, 0, INT_MAX );
  int f = moon_checkint( L, 4, 0, INT_MAX );
  int t = moon_checkint( L, 5, 0, INT_MAX );
  F4L_TRY {
    lua_pushinteger( L, s->scrollvalue( p, sz, f, t ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL void f4l_slider_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    F4L_SLIDER_METHODS,
    { "__index", slider_index },
    { "__newindex", slider_newindex },
    { NULL, NULL }
  };
  luaL_Reg const sb_methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    F4L_SLIDER_METHODS,
    { "setvalue", scrollbar_setvalue },
    { "__index", scrollbar_index },
    { "__newindex", scrollbar_newindex },
    { NULL, NULL }
  };
  luaL_Reg const vs_methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    F4L_SLIDER_METHODS,
    { "__index", value_slider_index },
    { "__newindex", value_slider_newindex },
  };

  moon_defobject( L, F4L_SLIDER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_SLIDER_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Slider, Fl_Valuator > );
  moon_defcast( L, F4L_SLIDER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Slider, Fl_Widget > );

  moon_defobject( L, F4L_SCROLLBAR_NAME, 0, sb_methods, 0 );
  moon_defcast( L, F4L_SCROLLBAR_NAME, F4L_SLIDER_NAME,
                f4l_cast< Fl_Scrollbar, Fl_Slider > );
  moon_defcast( L, F4L_SCROLLBAR_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Scrollbar, Fl_Valuator > );
  moon_defcast( L, F4L_SCROLLBAR_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Scrollbar, Fl_Widget > );

  moon_defobject( L, F4L_VALUE_SLIDER_NAME, 0, vs_methods, 0 );
  moon_defcast( L, F4L_VALUE_SLIDER_NAME, F4L_SLIDER_NAME,
                f4l_cast< Fl_Value_Slider, Fl_Slider > );
  moon_defcast( L, F4L_VALUE_SLIDER_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Value_Slider, Fl_Valuator > );
  moon_defcast( L, F4L_VALUE_SLIDER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Value_Slider, Fl_Widget > );

  f4l_new_class_table( L, "Slider", new_slider );
  f4l_new_class_table( L, "Scrollbar", new_scrollbar );
  f4l_new_class_table( L, "Value_Slider", new_value_slider );
}

