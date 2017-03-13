LIBS	=../API/SOs/lib_API_BrownArmor.so	\
	../API/SOs/lib_API_Butterfly.so		\
	../API/SOs/lib_API_Centiped.so		\
	../API/SOs/lib_API_Crab.so		\
	../API/SOs/lib_API_GreenArmor.so	\
	../API/SOs/lib_API_LittleShip.so	\
	../API/SOs/lib_API_MecaCrab.so		\
	../API/SOs/lib_API_MecaTurret.so	\
	../API/SOs/lib_API_RedArmor.so		\
	../API/SOs/lib_API_ShipMob.so		\
	../API/SOs/lib_API_Tentacle.so		\
	../API/SOs/lib_API_attack.so		\
	../API/SOs/lib_API_Bonus.so


all: $(LIBS)

$(LIBS):
	$(MAKE) -C BrownArmor all
	$(MAKE) -C Butterfly all
	$(MAKE) -C Centiped all
	$(MAKE) -C Crab all
	$(MAKE) -C GreenArmor all
	$(MAKE) -C LittleShip all
	$(MAKE) -C MecaCrab all
	$(MAKE) -C MecaTurret all
	$(MAKE) -C RedArmor all
	$(MAKE) -C ShipMob all
	$(MAKE) -C Tentacle all
	$(MAKE) -C attack all
	$(MAKE) -C Bonus all

clean:
	$(MAKE) -C BrownArmor clean
	$(MAKE) -C Butterfly clean
	$(MAKE) -C Centiped clean
	$(MAKE) -C Crab clean
	$(MAKE) -C GreenArmor clean
	$(MAKE) -C LittleShip clean
	$(MAKE) -C MecaCrab clean
	$(MAKE) -C MecaTurret clean
	$(MAKE) -C RedArmor clean
	$(MAKE) -C ShipMob clean
	$(MAKE) -C Tentacle clean
	$(MAKE) -C attack clean
	$(MAKE) -C Bonus clean

fclean:
	$(MAKE) -C BrownArmor fclean
	$(MAKE) -C Butterfly fclean
	$(MAKE) -C Centiped fclean
	$(MAKE) -C Crab fclean
	$(MAKE) -C GreenArmor fclean
	$(MAKE) -C LittleShip fclean
	$(MAKE) -C MecaCrab fclean
	$(MAKE) -C MecaTurret fclean
	$(MAKE) -C RedArmor fclean
	$(MAKE) -C ShipMob fclean
	$(MAKE) -C Tentacle fclean
	$(MAKE) -C attack fclean
	$(MAKE) -C Bonus fclean

re: fclean all

.PHONY: all clean fclean re
