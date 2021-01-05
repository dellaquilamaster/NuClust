CXXFLAGS = -g

all:
	$(MAKE) -C nuclear_masses  ;				$(MAKE) -C nuclear_masses install
	$(MAKE) -C RelativisticKinematics  ;			$(MAKE) -C RelativisticKinematics install
	$(MAKE) -C SRIMEnergyLossModule  ;			$(MAKE) -C SRIMEnergyLossModule install    
	$(MAKE) -C LISEEnergyLossModule  ;			$(MAKE) -C LISEEnergyLossModule install
	$(MAKE) -C RunningInfo  ;				$(MAKE) -C RunningInfo install
	$(MAKE) -C PixelizedDetectorData  ;			$(MAKE) -C PixelizedDetectorData install
	$(MAKE) -C ParticleIdentificationTools  ;		$(MAKE) -C ParticleIdentificationTools install

root:
	$(MAKE) -C nuclear_masses  ;				$(MAKE) -C nuclear_masses install
	$(MAKE) -C RelativisticKinematics  ;			$(MAKE) -C RelativisticKinematics install
	$(MAKE) -C SRIMEnergyLossModule  ;			$(MAKE) -C SRIMEnergyLossModule install    
	$(MAKE) -C LISEEnergyLossModule  ;			$(MAKE) -C LISEEnergyLossModule install
	$(MAKE) -C RunningInfo  ;				$(MAKE) -C RunningInfo install
	$(MAKE) -C PixelizedDetectorData  ;			$(MAKE) -C PixelizedDetectorData install
	$(MAKE) -C ParticleIdentificationTools  ;		$(MAKE) -C ParticleIdentificationTools install

install:
	$(MAKE) -C nuclear_masses install
	$(MAKE) -C RelativisticKinematics install
	$(MAKE) -C SRIMEnergyLossModule install    
	$(MAKE) -C LISEEnergyLossModule install
	$(MAKE) -C RunningInfo install
	$(MAKE) -C PixelizedDetectorData install
	$(MAKE) -C ParticleIdentificationTools install

distclean:
	$(MAKE) -C nuclear_masses distclean
	$(MAKE) -C RelativisticKinematics distclean
	$(MAKE) -C SRIMEnergyLossModule distclean
	$(MAKE) -C LISEEnergyLossModule distclean
	$(MAKE) -C RunningInfo distclean
	$(MAKE) -C PixelizedDetectorData distclean
	$(MAKE) -C ParticleIdentificationTools distclean

clean:
	$(MAKE) -C nuclear_masses clean
	$(MAKE) -C RelativisticKinematics clean
	$(MAKE) -C SRIMEnergyLossModule clean
	$(MAKE) -C LISEEnergyLossModule clean
	$(MAKE) -C RunningInfo clean
	$(MAKE) -C PixelizedDetectorData clean
	$(MAKE) -C ParticleIdentificationTools clean
