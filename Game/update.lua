function update()
	print("update")
	--Update framecounter
	frames=frames+1
	print("frames: " .. frames)
	
	--Instantiate new thin
	if frames % 5 == 1 then 
		local j=scene:NewEntity()
		j:SetPosition(math.sin(frames)*10,math.cos(frames)*7+5,3+math.sin(frames*7)*3)
		entities[#entities+1]=j
	end
	print("number of entities created: " .. #entities)
	
	--Simulate
	for e = 1,#entities do
		entity = entities[e]
		pos= entity:GetPosition()
		entity:SetPosition(pos.x,pos.y+pos.z*0.0015,pos.z+0.4)
	end
end

