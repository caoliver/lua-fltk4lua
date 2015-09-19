#!/usr/bin/env lua

local fl = require( "fltk4lua" )

local N = 0
local W = 70
local H = 70
local ROWS = 6
local COLS = 6

local window, orientation, size
local udatas = {}

local function slider_cb()
  local val = orientation.value
  local sze = size.value
  for i = window.children-1, 0, -1 do
    local wc = window:child( i )
    local l = udatas[ wc ]
    if l and l:match( "^@" ) then
      l = l:sub( 2 )
      if val ~= 0 and sze ~= 0 then
        l = ("@%+d%d%s"):format( sze, val, l )
      elseif val ~= 0 then
        l = ("@%d%s"):format( val, l )
      elseif sze ~= 0 then
        l = ("@%+d%s"):format( sze, l )
      else
        l = ("@%s"):format( l )
      end
      if wc.box == "FL_NO_BOX" then
        l = "@"..l
      end
      wc.label = l
    end
  end
  window:redraw()
end

local function bt( name )
  local x = N % COLS
  local y = (N - x)/COLS
  N = N + 1
  x = x * W + 10
  y = y * H + 10
  local b1 = fl.Box( x, y, W-20, H-20, "@"..name )
  b1.box = "FL_NO_BOX"
  b1.align = fl.ALIGN_BOTTOM
  b1.labelsize = 11
  udatas[ b1 ] = name
  local b2 = fl.Box( x, y, W-20, H-20, name )
  b2.box = "FL_UP_BOX"
  b2.labelcolor = fl.DARK3
  udatas[ b2 ] = name
end

window = fl.Window( COLS*W, ROWS*H+60 )
bt( "@->" )
bt( "@>" )
bt( "@>>" )
bt( "@>|" )
bt( "@>[]" )
bt( "@|>" )
bt( "@<-" )
bt( "@<" )
bt( "@<<" )
bt( "@|<" )
bt( "@[]<" )
bt( "@<|" )
bt( "@<->" )
bt( "@-->" )
bt( "@+" )
bt( "@->|" )
bt( "@||" )
bt( "@arrow" )
bt( "@returnarrow" )
bt( "@square" )
bt( "@circle" )
bt( "@line" )
bt( "@menu" )
bt( "@UpArrow" )
bt( "@DnArrow" )
bt( "@search" )
bt( "@FLTK" )
bt( "@filenew" )
bt( "@fileopen" )
bt( "@filesave" )
bt( "@filesaveas" )
bt( "@fileprint" )
bt( "@refresh" )
bt( "@reload" )
bt( "@undo" )
bt( "@redo" )

local x = math.floor( window.w * 0.05 + 0.5 )
local w = math.floor( window.w * 0.42 + 0.5 )
orientation = fl.Hor_Value_Slider( x, window.h-40, w, 16, "Orientation" )
orientation:range( 0.0, 9.0 )
orientation.value = 0.0
orientation.step = 1
orientation.callback = slider_cb
x = math.floor( window.w * 0.53 + 0.5 )
size = fl.Hor_Value_Slider( x, window.h-40, w, 16, "Size" )
size:range( -3.0, 9.0 )
size.value = 0.0
size.step = 1
size.callback = slider_cb

window.resizable = window
window:show( arg )
fl.run()
