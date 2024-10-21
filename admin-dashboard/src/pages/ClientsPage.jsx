import Header from "../components/common/Header";
import StatCard from '../components/common/StatCard'
import ClientsTable from '../components/clients/ClientsTable'
import ClientGrowthChart from '../components/clients/ClientGrowthChart'
import ClientActivityHeatmap from '../components/clients/ClientActivityHeatmap'
import ClientDemographicsChart from '../components/clients/ClientDemographicsChart'
import { UsersIcon, UserPlus, UserCheck, UserX } from 'lucide-react'
import { motion } from "framer-motion"
import { useState, useEffect } from "react";
import { useNavigate } from "react-router-dom";

const userStats = {
	totalUsers: 152845,
	newUsersToday: 243,
	activeUsers: 98520,
	churnRate: "2.4%",
};

// const allClients = [
// 	{ id: 1, name: "John Doe", cuit: "john@example.com", role: "Customer", status: "Active" },
// 	{ id: 2, name: "Jane Smith", cuit: "jane@example.com", role: "Admin", status: "Active" },
// 	{ id: 3, name: "Bob Johnson", cuit: "bob@example.com", role: "Customer", status: "Inactive" },
// 	{ id: 4, name: "Alice Brown", cuit: "alice@example.com", role: "Customer", status: "Active" },
// 	{ id: 5, name: "Charlie Wilson", cuit: "charlie@example.com", role: "Moderator", status: "Active" },
// ];

const ClientsPage = () => {
    const [totalClients, setTotalClients] = useState([]);
    const [totalClientsLength, setTotalClientsLength] = useState(0);
    const navigate = useNavigate();

    const fetchData = async () => {
        try{
            // Llamada para obtener total de clientes
            const allClientsResponse = await fetch('http://localhost:9080/clientes');
            const allClientsData = await allClientsResponse.json();
            setTotalClients(allClientsData);
            setTotalClientsLength(allClientsData.length);

        } catch (error) {
            console.error('Error fetching data:', error);
        }
    };

    useEffect(() => {
        fetchData();
    }, []);

    return (
        <div className="flex-1 overflow-auto relative z-10">
            <Header title="Clients" /> 
            <main className='max-w-7x1 mx-auto py-6 px-4 lg:px-8'>
                {/* STATS */}
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-2 mb-8'
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1 }}
                >
                    <StatCard
						name='Total Clientes'
						icon={UsersIcon}
						value={totalClientsLength}
						color='#6366F1'
					/>
					<StatCard 
                        name='Agergar Cliente' 
                        icon={UserPlus} 
                        value="Nuevo" 
                        color='#10B981'
                        onClick={() => navigate('/agregar-cliente')}
                    />
					{/* <StatCard
						name='Active Users'
						icon={UserCheck}
						value={userStats.activeUsers.toLocaleString()}
						color='#F59E0B'
					/> */}
					{/* <StatCard name='Churn Rate' icon={UserX} value={userStats.churnRate} color='#EF4444' /> */}
                </motion.div>
                
                <ClientsTable totalClients={ totalClients }/>

                {/* CLIENT CHARTS */}
                <div className="grid grid-cols-1 lg:grid-cols-2 gap-6 mt-8">
                    {/* <ClientGrowthChart />
                    <ClientActivityHeatmap />
                    <ClientDemographicsChart /> */}
                </div>
            </main>
        </div>
    );
};

export default ClientsPage;