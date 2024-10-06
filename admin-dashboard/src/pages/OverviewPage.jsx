import { BarChart2, ShoppingBag, Zap, Users } from 'lucide-react'
import Header from '../components/common/Header'
import StatCard from '../components/common/StatCard'
import SalesOverviewChart from '../components/overview/SalesOverviewChart'

import { motion } from 'framer-motion'

const OverviewPage = () => {
    return (
        <div className="flex-1 overflow-auto relative z-10">
            <Header title="Overview" />

            <main className='max-w-7x1 mx-auto py-6 px-4 lg:px-8'>
                {/* STATS */}
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-4 mb-8'
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1 }}
                >
                    <StatCard name="Total Sales" icon={Zap} value="2,390" color="#6366F1" />
                    <StatCard name="Total Products" icon={ShoppingBag} value="1,200" color="#EC4899" />
                    <StatCard name="New Users" icon={Users} value="1,200" color="#8B5CF6" />
                    <StatCard name="Convertion Rate" icon={BarChart2} value="12.5%" color="##10B981" />
                    
                </motion.div>

                {/* CHARTS */}
                <div className='grid grid-col-1 lg:grid-col-2 gap-8'>
                    <SalesOverviewChart />
                </div>
            </main>
        </div>
    )
} 

export default OverviewPage