function frameSq = drawbox(frame,cornerX,cornerY,width,height)
%code to draw a square in an image

frameSq = insertShape(frame,'Rectangle',[cornerX cornerY width height],'LineWidth',3,'Color','yellow');

end