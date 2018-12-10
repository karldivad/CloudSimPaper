/*
 * CloudSim Plus: A modern, highly-extensible and easier-to-use Framework for
 * Modeling and Simulation of Cloud Computing Infrastructures and Services.
 * http://cloudsimplus.org
 *
 *     Copyright (C) 2015-2018 Universidade da Beira Interior (UBI, Portugal) and
 *     the Instituto Federal de Educação Ciência e Tecnologia do Tocantins (IFTO, Brazil).
 *
 *     This file is part of CloudSim Plus.
 *
 *     CloudSim Plus is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     CloudSim Plus is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with CloudSim Plus. If not, see <http://www.gnu.org/licenses/>.
 */
package org.cloudsimplus.examples.dynamic;

import org.cloudbus.cloudsim.allocationpolicies.VmAllocationPolicySimple;
import org.cloudbus.cloudsim.brokers.DatacenterBroker;
import org.cloudbus.cloudsim.brokers.DatacenterBrokerSimple;
import org.cloudbus.cloudsim.cloudlets.Cloudlet;
import org.cloudbus.cloudsim.cloudlets.CloudletSimple;
import org.cloudbus.cloudsim.core.CloudSim;
import org.cloudbus.cloudsim.core.CloudSimTags;
import org.cloudbus.cloudsim.datacenters.Datacenter;
import org.cloudbus.cloudsim.datacenters.DatacenterSimple;
import org.cloudbus.cloudsim.hosts.Host;
import org.cloudbus.cloudsim.hosts.HostSimple;
import org.cloudbus.cloudsim.provisioners.PeProvisionerSimple;
import org.cloudbus.cloudsim.provisioners.ResourceProvisionerSimple;
import org.cloudbus.cloudsim.resources.Pe;
import org.cloudbus.cloudsim.resources.PeSimple;
import org.cloudbus.cloudsim.schedulers.cloudlet.CloudletSchedulerTimeShared;
import org.cloudbus.cloudsim.schedulers.vm.VmSchedulerTimeShared;
import org.cloudbus.cloudsim.utilizationmodels.UtilizationModelDynamic;
import org.cloudbus.cloudsim.utilizationmodels.UtilizationModelFull;
import org.cloudbus.cloudsim.vms.Vm;
import org.cloudbus.cloudsim.vms.VmSimple;
import org.cloudsimplus.builders.tables.CloudletsTableBuilder;
import org.cloudsimplus.listeners.EventInfo;
import org.cloudsimplus.listeners.EventListener;

import java.util.ArrayList;
import java.util.List;

/**
 * A example showing how to create Cloudlets with an indefinite length,
 * so that each Cloudlet stops running only if:
 * <ul>
 *  <li>(i) it reaches {@link Long#MAX_VALUE} MI executed or</li>
 *  <li>(ii) {@link CloudSimTags#CLOUDLET_FINISH} message is sent to the {@link DatacenterBroker}.</li>
 * </ul>
 *
 * In this example, the Cloudlets that initially with an indefinite length
 * will have a length set when the first created Cloudlet (one with a predefined
 * length) finishes. In such a moment, the length of the other Cloudlets is set.
 *
 * <p>The time or event when the length of such Cloudlets are set
 * can be defined in uncountable ways, according to developer needs.</p>
 *
 * @author Manoel Campos da Silva Filho
 * @since CloudSim Plus 4.0.0
 */
public class IndefiniteLengthCloudlet {
    private static final int HOSTS = 1;
    private static final int HOST_PES = 8;

    private static final int VMS = 2;
    private static final int VM_PES = 4;
    private static final int VM_MIPS = 1000;

    private static final int CLOUDLETS = 1;
    private static final int CLOUDLET_PES = 2;

    private final CloudSim simulation;
    private DatacenterBroker broker0;
    private List<Vm> vmList;
    private List<Cloudlet> cloudletList;
    private Datacenter datacenter0;

    public static void main(String[] args) {
        new IndefiniteLengthCloudlet();
    }

    private IndefiniteLengthCloudlet() {
        /*Enables just some level of log messages.
          Make sure to import org.cloudsimplus.util.Log;*/
        //Log.setLevel(ch.qos.logback.classic.Level.WARN);

        simulation = new CloudSim();
        datacenter0 = createDatacenter();

        //Creates a broker that is a software acting on behalf a cloud customer to manage his/her VMs and Cloudlets
        broker0 = new DatacenterBrokerSimple(simulation);

        vmList = createVms();

        cloudletList = createCloudlets();
        broker0.submitVmList(vmList);
        broker0.submitCloudletList(cloudletList);

        simulation.addOnSimulationStartListener(this::sendCloudletFinishMsg);
        simulation.start();

        final List<Cloudlet> finishedCloudlets = broker0.getCloudletFinishedList();
        new CloudletsTableBuilder(finishedCloudlets).build();
    }

    /**
     * After the simulation starts, send a {@link CloudSimTags#CLOUDLET_FINISH} message
     * with a specific delay defining the time when the Cloudlets with an indefinite length
     * will finish.
     *
     * <p>This method is an {@link org.cloudsimplus.listeners.EventListener} that will be
     * called after the simulation starts.</p>
     * @param info the simulation start event information
     * @see CloudSim#addOnSimulationStartListener(EventListener)
     */
    private void sendCloudletFinishMsg(final EventInfo info) {
        System.out.println("Sending cloudlets finish message");
        cloudletList.forEach(cloudlet -> broker0.schedule(400, CloudSimTags.CLOUDLET_FINISH, cloudlet));
    }

    /**
     * Creates a Datacenter and its Hosts.
     */
    private Datacenter createDatacenter() {
        final List<Host> hostList = new ArrayList<>(HOSTS);
        for(int i = 0; i < HOSTS; i++) {
            Host host = createHost();
            hostList.add(host);
        }

        return new DatacenterSimple(simulation, hostList, new VmAllocationPolicySimple());
    }

    private Host createHost() {
        List<Pe> peList = new ArrayList<>(HOST_PES);
        //List of Host's CPUs (Processing Elements, PEs)
        for (int i = 0; i < HOST_PES; i++) {
            peList.add(new PeSimple(1000, new PeProvisionerSimple()));
        }

        final long ram = 2048; //in Megabytes
        final long bw = 10000; //in Megabits/s
        final long storage = 1000000; //in Megabytes
        Host host = new HostSimple(ram, bw, storage, peList);
        host
            .setRamProvisioner(new ResourceProvisionerSimple())
            .setBwProvisioner(new ResourceProvisionerSimple())
            .setVmScheduler(new VmSchedulerTimeShared());
        return host;
    }

    /**
     * Creates a list of VMs.
     */
    private List<Vm> createVms() {
        final List<Vm> list = new ArrayList<>(VMS);
        for (int i = 0; i < VMS; i++) {
            Vm vm =
                new VmSimple(i, VM_MIPS, VM_PES)
                    .setRam(512).setBw(1000).setSize(10000)
                    .setCloudletScheduler(new CloudletSchedulerTimeShared());

            list.add(vm);
        }

        return list;
    }

    /**
     * Creates Cloudlets with indefinite length by setting a negative value.
     * This way, the Cloudlets keep running until a {@link CloudSimTags#CLOUDLET_FINISH}
     * event is sent to the {@link DatacenterBroker}.
     * @see #sendCloudletFinishMsg(EventInfo)
     */
    private List<Cloudlet> createCloudlets() {
        final List<Cloudlet> list = new ArrayList<>(CLOUDLETS);
        final UtilizationModelFull utilizationFull = new UtilizationModelFull();
        final UtilizationModelDynamic utilizationDynamic = new UtilizationModelDynamic(1.0/CLOUDLETS);

        for (int i = 0; i < CLOUDLETS; i++) {
            Cloudlet cloudlet =
                new CloudletSimple(-10000, CLOUDLET_PES)
                    .setFileSize(1024)
                    .setOutputSize(1024)
                    .setUtilizationModelCpu(utilizationFull)
                    .setUtilizationModelRam(utilizationDynamic)
                    .setUtilizationModelBw(utilizationDynamic);
            list.add(cloudlet);
        }
        return list;
    }
}
