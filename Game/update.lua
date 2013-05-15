function update()
	print("update")
	frames=frames+1
	print("frames: " .. frames)
	
	if frames % 100 == 1 then 
		local j=scene:NewEntity()
		j:SetPosition(math.sin(frames)*5,math.cos(frames)*10,3)
	end
end

