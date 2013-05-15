function update()
	print("update")
	frames=frames+1
	print("frames: " .. frames)
	
	if frames % 10 == 1 then 
		local j=scene:NewEntity()
		j:SetPosition(math.sin(frames)*10,math.cos(frames)*5+5,3+math.sin(frames*7)*3)
	end
end

